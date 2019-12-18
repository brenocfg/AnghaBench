#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hpsb_iso {int dummy; } ;
struct firedtv {struct hpsb_iso* backend_data; int /*<<< orphan*/  device; int /*<<< orphan*/  isochannel; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FDTV_ISO_BUFFER_PACKETS ; 
 int /*<<< orphan*/  FDTV_ISO_BUFFER_SIZE ; 
 int /*<<< orphan*/  HPSB_ISO_DMA_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hpsb_iso* hpsb_iso_recv_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int hpsb_iso_recv_start (struct hpsb_iso*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_iso_shutdown (struct hpsb_iso*) ; 
 TYPE_1__* node_of (struct firedtv*) ; 
 int /*<<< orphan*/  rawiso_activity_cb ; 

__attribute__((used)) static int start_iso(struct firedtv *fdtv)
{
	struct hpsb_iso *iso_handle;
	int ret;

	iso_handle = hpsb_iso_recv_init(node_of(fdtv)->host,
				FDTV_ISO_BUFFER_SIZE, FDTV_ISO_BUFFER_PACKETS,
				fdtv->isochannel, HPSB_ISO_DMA_DEFAULT,
				-1, /* stat.config.irq_interval */
				rawiso_activity_cb);
	if (iso_handle == NULL) {
		dev_err(fdtv->device, "cannot initialize iso receive\n");
		return -ENOMEM;
	}
	fdtv->backend_data = iso_handle;

	ret = hpsb_iso_recv_start(iso_handle, -1, -1, 0);
	if (ret != 0) {
		dev_err(fdtv->device, "cannot start iso receive\n");
		hpsb_iso_shutdown(iso_handle);
		fdtv->backend_data = NULL;
	}
	return ret;
}