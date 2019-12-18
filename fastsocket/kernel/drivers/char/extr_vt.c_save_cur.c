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
struct vc_data {int /*<<< orphan*/  vc_G1_charset; int /*<<< orphan*/  vc_saved_G1; int /*<<< orphan*/  vc_G0_charset; int /*<<< orphan*/  vc_saved_G0; int /*<<< orphan*/  vc_color; int /*<<< orphan*/  vc_s_color; int /*<<< orphan*/  vc_charset; int /*<<< orphan*/  vc_s_charset; int /*<<< orphan*/  vc_reverse; int /*<<< orphan*/  vc_s_reverse; int /*<<< orphan*/  vc_blink; int /*<<< orphan*/  vc_s_blink; int /*<<< orphan*/  vc_underline; int /*<<< orphan*/  vc_s_underline; int /*<<< orphan*/  vc_italic; int /*<<< orphan*/  vc_s_italic; int /*<<< orphan*/  vc_intensity; int /*<<< orphan*/  vc_s_intensity; int /*<<< orphan*/  vc_y; int /*<<< orphan*/  vc_saved_y; int /*<<< orphan*/  vc_x; int /*<<< orphan*/  vc_saved_x; } ;

/* Variables and functions */

__attribute__((used)) static void save_cur(struct vc_data *vc)
{
	vc->vc_saved_x		= vc->vc_x;
	vc->vc_saved_y		= vc->vc_y;
	vc->vc_s_intensity	= vc->vc_intensity;
	vc->vc_s_italic         = vc->vc_italic;
	vc->vc_s_underline	= vc->vc_underline;
	vc->vc_s_blink		= vc->vc_blink;
	vc->vc_s_reverse	= vc->vc_reverse;
	vc->vc_s_charset	= vc->vc_charset;
	vc->vc_s_color		= vc->vc_color;
	vc->vc_saved_G0		= vc->vc_G0_charset;
	vc->vc_saved_G1		= vc->vc_G1_charset;
}