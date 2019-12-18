#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ uuid_le ;
typedef  size_t u32 ;
struct TYPE_7__ {int /*<<< orphan*/  guid; } ;
struct TYPE_6__ {size_t* vp_index; } ;

/* Variables and functions */
 int IDE ; 
 int MAX_PERF_CHN ; 
 scalar_t__ VERSION_WIN7 ; 
 scalar_t__ VERSION_WS2008 ; 
 TYPE_3__* hp_devs ; 
 TYPE_2__ hv_context ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t next_vp ; 
 size_t num_online_cpus () ; 
 scalar_t__ vmbus_proto_version ; 

__attribute__((used)) static u32 get_vp_index(uuid_le *type_guid)
{
	u32 cur_cpu;
	int i;
	bool perf_chn = false;
	u32 max_cpus = num_online_cpus();

	for (i = IDE; i < MAX_PERF_CHN; i++) {
		if (!memcmp(type_guid->b, hp_devs[i].guid,
				 sizeof(uuid_le))) {
			perf_chn = true;
			break;
		}
	}
	if ((vmbus_proto_version == VERSION_WS2008) ||
	    (vmbus_proto_version == VERSION_WIN7) || (!perf_chn)) {
		/*
		 * Prior to win8, all channel interrupts are
		 * delivered on cpu 0.
		 * Also if the channel is not a performance critical
		 * channel, bind it to cpu 0.
		 */
		return 0;
	}
	cur_cpu = (++next_vp % max_cpus);
	return hv_context.vp_index[cur_cpu];
}