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
struct TYPE_3__ {int width; int height; } ;
struct vc_data {scalar_t__ vc_mode; TYPE_1__ vc_font; } ;
struct fb_info {scalar_t__ node; } ;
struct fb_blit_caps {int x; int y; int len; scalar_t__ flags; } ;
struct display {int /*<<< orphan*/  fontdata; scalar_t__ userfont; } ;
struct TYPE_4__ {struct vc_data* d; } ;

/* Variables and functions */
 int FNTCHARCNT (int /*<<< orphan*/ ) ; 
 scalar_t__ KD_TEXT ; 
 scalar_t__* con2fb_map ; 
 struct display* fb_display ; 
 size_t fg_console ; 
 int first_fb_vc ; 
 int last_fb_vc ; 
 TYPE_2__* vc_cons ; 

__attribute__((used)) static void fbcon_get_requirement(struct fb_info *info,
				  struct fb_blit_caps *caps)
{
	struct vc_data *vc;
	struct display *p;

	if (caps->flags) {
		int i, charcnt;

		for (i = first_fb_vc; i <= last_fb_vc; i++) {
			vc = vc_cons[i].d;
			if (vc && vc->vc_mode == KD_TEXT &&
			    info->node == con2fb_map[i]) {
				p = &fb_display[i];
				caps->x |= 1 << (vc->vc_font.width - 1);
				caps->y |= 1 << (vc->vc_font.height - 1);
				charcnt = (p->userfont) ?
					FNTCHARCNT(p->fontdata) : 256;
				if (caps->len < charcnt)
					caps->len = charcnt;
			}
		}
	} else {
		vc = vc_cons[fg_console].d;

		if (vc && vc->vc_mode == KD_TEXT &&
		    info->node == con2fb_map[fg_console]) {
			p = &fb_display[fg_console];
			caps->x = 1 << (vc->vc_font.width - 1);
			caps->y = 1 << (vc->vc_font.height - 1);
			caps->len = (p->userfont) ?
				FNTCHARCNT(p->fontdata) : 256;
		}
	}
}