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
struct vc_data {int /*<<< orphan*/  vc_screenbuf_size; int /*<<< orphan*/  vc_video_erase_char; } ;

/* Variables and functions */
 int MDA_MODE_BLINK_EN ; 
 int MDA_MODE_VIDEO_EN ; 
 scalar_t__ TYPE_MDA ; 
 int /*<<< orphan*/  mda_convert_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mda_mode_port ; 
 scalar_t__ mda_type ; 
 scalar_t__ mda_vram_base ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scr_memsetw (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdacon_blank(struct vc_data *c, int blank, int mode_switch)
{
	if (mda_type == TYPE_MDA) {
		if (blank) 
			scr_memsetw((void *)mda_vram_base, 
				mda_convert_attr(c->vc_video_erase_char),
				c->vc_screenbuf_size);
		/* Tell console.c that it has to restore the screen itself */
		return 1;
	} else {
		if (blank)
			outb_p(0x00, mda_mode_port);	/* disable video */
		else
			outb_p(MDA_MODE_VIDEO_EN | MDA_MODE_BLINK_EN, 
				mda_mode_port);
		return 0;
	}
}