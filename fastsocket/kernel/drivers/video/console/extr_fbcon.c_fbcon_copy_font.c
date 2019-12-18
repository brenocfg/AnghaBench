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
struct console_font {scalar_t__ data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct vc_data {struct console_font vc_font; } ;
struct display {scalar_t__ fontdata; int /*<<< orphan*/  userfont; } ;

/* Variables and functions */
 struct display* fb_display ; 
 int fbcon_do_set_font (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fbcon_copy_font(struct vc_data *vc, int con)
{
	struct display *od = &fb_display[con];
	struct console_font *f = &vc->vc_font;

	if (od->fontdata == f->data)
		return 0;	/* already the same font... */
	return fbcon_do_set_font(vc, f->width, f->height, od->fontdata, od->userfont);
}