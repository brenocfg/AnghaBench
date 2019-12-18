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
 void* FALSE ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playbackfp ; 
 void* playingback ; 
 int /*<<< orphan*/  recordfp ; 
 void* recording ; 

void INPUT_Exit(void) {
#ifdef EVENT_RECORDING
	if (recording) {
		gzclose(recordfp);
		recording = FALSE;
	}
	if (playingback) {
		gzclose(playbackfp);
		playingback = FALSE;
	}
#endif
}