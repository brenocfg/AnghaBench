#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p; } ;
struct TYPE_8__ {size_t number; TYPE_1__ hdr; } ;
typedef  TYPE_2__ wavefront_patch_info ;
struct TYPE_9__ {int /*<<< orphan*/ * patch_status; } ;
typedef  TYPE_3__ snd_wavefront_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ,char*,size_t) ; 
 int EIO ; 
 int /*<<< orphan*/  WFC_DOWNLOAD_PATCH ; 
 int /*<<< orphan*/  WF_DEBUG_LOAD_PATCH ; 
 int /*<<< orphan*/  WF_PATCH_BYTES ; 
 int /*<<< orphan*/  WF_SLOT_FILLED ; 
 int /*<<< orphan*/  munge_buf (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char* munge_int32 (size_t,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_printk (char*) ; 
 scalar_t__ snd_wavefront_cmd (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int
wavefront_send_patch (snd_wavefront_t *dev, wavefront_patch_info *header)

{
	unsigned char buf[WF_PATCH_BYTES+2];
	unsigned char *bptr;

	DPRINT (WF_DEBUG_LOAD_PATCH, "downloading patch %d\n",
				      header->number);

	dev->patch_status[header->number] |= WF_SLOT_FILLED;

	bptr = buf;
	bptr = munge_int32 (header->number, buf, 2);
	munge_buf ((unsigned char *)&header->hdr.p, bptr, WF_PATCH_BYTES);
    
	if (snd_wavefront_cmd (dev, WFC_DOWNLOAD_PATCH, NULL, buf)) {
		snd_printk ("download patch failed\n");
		return -(EIO);
	}

	return (0);
}