#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  trans_id; int /*<<< orphan*/  type; } ;
struct dm_balloon_response {int more_pages; int range_count; int /*<<< orphan*/ * range_array; TYPE_3__ hdr; } ;
struct TYPE_7__ {int num_pages; } ;
struct TYPE_10__ {TYPE_2__* dev; int /*<<< orphan*/  state; TYPE_1__ balloon_wrk; } ;
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_BALLOON_RESPONSE ; 
 int /*<<< orphan*/  DM_INITIALIZED ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int alloc_balloon_pages (TYPE_4__*,int,struct dm_balloon_response*,int,int*) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 TYPE_4__ dm_device ; 
 int /*<<< orphan*/  free_balloon_pages (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ send_buffer ; 
 int /*<<< orphan*/  trans_id ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct dm_balloon_response*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void balloon_up(struct work_struct *dummy)
{
	int num_pages = dm_device.balloon_wrk.num_pages;
	int num_ballooned = 0;
	struct dm_balloon_response *bl_resp;
	int alloc_unit;
	int ret;
	bool alloc_error = false;
	bool done = false;
	int i;


	/*
	 * We will attempt 2M allocations. However, if we fail to
	 * allocate 2M chunks, we will go back to 4k allocations.
	 */
	alloc_unit = 512;

	while (!done) {
		bl_resp = (struct dm_balloon_response *)send_buffer;
		memset(send_buffer, 0, PAGE_SIZE);
		bl_resp->hdr.type = DM_BALLOON_RESPONSE;
		bl_resp->hdr.size = sizeof(struct dm_balloon_response);
		bl_resp->more_pages = 1;


		num_pages -= num_ballooned;
		num_ballooned = alloc_balloon_pages(&dm_device, num_pages,
						bl_resp, alloc_unit,
						 &alloc_error);

		if ((alloc_error) && (alloc_unit != 1)) {
			alloc_unit = 1;
			continue;
		}

		if ((alloc_error) || (num_ballooned == num_pages)) {
			bl_resp->more_pages = 0;
			done = true;
			dm_device.state = DM_INITIALIZED;
		}

		/*
		 * We are pushing a lot of data through the channel;
		 * deal with transient failures caused because of the
		 * lack of space in the ring buffer.
		 */

		do {
			bl_resp->hdr.trans_id = atomic_inc_return(&trans_id);
			ret = vmbus_sendpacket(dm_device.dev->channel,
						bl_resp,
						bl_resp->hdr.size,
						(unsigned long)NULL,
						VM_PKT_DATA_INBAND, 0);

			if (ret == -EAGAIN)
				msleep(20);

		} while (ret == -EAGAIN);

		if (ret) {
			/*
			 * Free up the memory we allocatted.
			 */
			pr_info("Balloon response failed\n");

			for (i = 0; i < bl_resp->range_count; i++)
				free_balloon_pages(&dm_device,
						 &bl_resp->range_array[i]);

			done = true;
		}
	}

}