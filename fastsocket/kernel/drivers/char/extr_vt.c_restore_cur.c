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
struct vc_data {scalar_t__ vc_need_wrap; int /*<<< orphan*/  vc_G0_charset; int /*<<< orphan*/  vc_G1_charset; scalar_t__ vc_charset; int /*<<< orphan*/  vc_translate; int /*<<< orphan*/  vc_saved_G1; int /*<<< orphan*/  vc_saved_G0; int /*<<< orphan*/  vc_s_color; int /*<<< orphan*/  vc_color; scalar_t__ vc_s_charset; int /*<<< orphan*/  vc_s_reverse; int /*<<< orphan*/  vc_reverse; int /*<<< orphan*/  vc_s_blink; int /*<<< orphan*/  vc_blink; int /*<<< orphan*/  vc_s_underline; int /*<<< orphan*/  vc_underline; int /*<<< orphan*/  vc_s_italic; int /*<<< orphan*/  vc_italic; int /*<<< orphan*/  vc_s_intensity; int /*<<< orphan*/  vc_intensity; int /*<<< orphan*/  vc_saved_y; int /*<<< orphan*/  vc_saved_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  gotoxy (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_translate (int /*<<< orphan*/ ,struct vc_data*) ; 
 int /*<<< orphan*/  update_attr (struct vc_data*) ; 

__attribute__((used)) static void restore_cur(struct vc_data *vc)
{
	gotoxy(vc, vc->vc_saved_x, vc->vc_saved_y);
	vc->vc_intensity	= vc->vc_s_intensity;
	vc->vc_italic		= vc->vc_s_italic;
	vc->vc_underline	= vc->vc_s_underline;
	vc->vc_blink		= vc->vc_s_blink;
	vc->vc_reverse		= vc->vc_s_reverse;
	vc->vc_charset		= vc->vc_s_charset;
	vc->vc_color		= vc->vc_s_color;
	vc->vc_G0_charset	= vc->vc_saved_G0;
	vc->vc_G1_charset	= vc->vc_saved_G1;
	vc->vc_translate	= set_translate(vc->vc_charset ? vc->vc_G1_charset : vc->vc_G0_charset, vc);
	update_attr(vc);
	vc->vc_need_wrap = 0;
}