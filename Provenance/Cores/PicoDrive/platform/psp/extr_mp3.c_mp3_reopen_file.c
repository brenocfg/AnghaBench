#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  PSP_O_RDONLY ; 
 int /*<<< orphan*/  PSP_SEEK_SET ; 
 int /*<<< orphan*/  lprintf (char*,char*) ; 
 char* mp3_fname ; 
 scalar_t__ mp3_handle ; 
 int /*<<< orphan*/  mp3_src_pos ; 
 int /*<<< orphan*/  sceIoClose (scalar_t__) ; 
 int /*<<< orphan*/  sceIoLseek32 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sceIoOpen (char*,int /*<<< orphan*/ ,int) ; 

void mp3_reopen_file(void)
{
	if (mp3_fname == NULL) return;
	lprintf("mp3_reopen_file(%s)\n", mp3_fname);

	// try closing, just in case
	if (mp3_handle >= 0) sceIoClose(mp3_handle);

	mp3_handle = sceIoOpen(mp3_fname, PSP_O_RDONLY, 0777);
	if (mp3_handle >= 0)
		sceIoLseek32(mp3_handle, mp3_src_pos, PSP_SEEK_SET);
	lprintf("mp3_reopen_file %s\n", mp3_handle >= 0 ? "ok" : "failed");
}