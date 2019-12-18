#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* reg; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 scalar_t__ VRAM_CACHED_STUFF ; 
 scalar_t__ VRAM_STUFF ; 
 int /*<<< orphan*/  amips_clut_f (unsigned short*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  localPal ; 

__attribute__((used)) static void do_slowmode_lines(int line_to)
{
	int line = 0, line_len = (Pico.video.reg[12]&1) ? 320 : 256;
	unsigned short *dst = (unsigned short *)VRAM_STUFF + 512*240/2;
	unsigned char  *src = (unsigned char  *)VRAM_CACHED_STUFF + 16;
	if (!(Pico.video.reg[1]&8)) { line = 8; dst += 512*8; src += 512*8; }

	for (; line < line_to; line++, dst+=512, src+=512)
		amips_clut_f(dst, src, localPal, line_len);
}