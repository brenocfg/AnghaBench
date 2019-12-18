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
struct TYPE_7__ {int /*<<< orphan*/  PatchNumber; } ;
struct TYPE_5__ {TYPE_3__ d; } ;
struct TYPE_6__ {int number; TYPE_1__ hdr; } ;
typedef  TYPE_2__ wavefront_patch_info ;
typedef  TYPE_3__ wavefront_drum ;
typedef  int /*<<< orphan*/  snd_wavefront_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  WFC_DOWNLOAD_EDRUM_PROGRAM ; 
 int /*<<< orphan*/  WF_DEBUG_LOAD_PATCH ; 
 int WF_DRUM_BYTES ; 
 int /*<<< orphan*/  munge_int32 (unsigned char,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_printk (char*) ; 
 scalar_t__ snd_wavefront_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static int
wavefront_send_drum (snd_wavefront_t *dev, wavefront_patch_info *header)

{
	unsigned char drumbuf[WF_DRUM_BYTES];
	wavefront_drum *drum = &header->hdr.d;
	int i;

	DPRINT (WF_DEBUG_LOAD_PATCH, "downloading edrum for MIDI "
		"note %d, patch = %d\n", 
		header->number, drum->PatchNumber);

	drumbuf[0] = header->number & 0x7f;

	for (i = 0; i < 4; i++) {
		munge_int32 (((unsigned char *)drum)[i], &drumbuf[1+(i*2)], 2);
	}

	if (snd_wavefront_cmd (dev, WFC_DOWNLOAD_EDRUM_PROGRAM, NULL, drumbuf)) {
		snd_printk ("download drum failed.\n");
		return -(EIO);
	}

	return (0);
}