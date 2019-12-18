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
struct vc_data {int vc_screenbuf_size; int vc_hi_font_mask; int vc_video_erase_char; scalar_t__ vc_origin; } ;

/* Variables and functions */
 int scr_readw (unsigned short*) ; 
 int /*<<< orphan*/  scr_writew (int,unsigned short*) ; 

__attribute__((used)) static void clear_buffer_attributes(struct vc_data *vc)
{
	unsigned short *p = (unsigned short *)vc->vc_origin;
	int count = vc->vc_screenbuf_size / 2;
	int mask = vc->vc_hi_font_mask | 0xff;

	for (; count > 0; count--, p++) {
		scr_writew((scr_readw(p)&mask) | (vc->vc_video_erase_char & ~mask), p);
	}
}