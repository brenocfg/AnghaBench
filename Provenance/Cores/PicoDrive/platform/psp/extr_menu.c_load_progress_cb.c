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
 int lcdr_line ; 
 int /*<<< orphan*/  memset (unsigned short*,int,int) ; 
 scalar_t__ menu_screen ; 

__attribute__((used)) static void load_progress_cb(int percent)
{
	int ln, len = percent * 480 / 100;
	unsigned short *dst;

	//sceDisplayWaitVblankStart();

	dst = (unsigned short *)menu_screen + 512*10*lcdr_line;

	if (len > 480) len = 480;
	for (ln = 8; ln > 0; ln--, dst += 512)
		memset(dst, 0xff, len*2);
}