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
struct vc_data {int /*<<< orphan*/  vc_cols; int /*<<< orphan*/  vc_rows; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK ; 
 int /*<<< orphan*/  sti_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sticon_set_origin (struct vc_data*) ; 
 int /*<<< orphan*/  sticon_sti ; 
 int vga_is_gfx ; 

__attribute__((used)) static int sticon_blank(struct vc_data *c, int blank, int mode_switch)
{
    if (blank == 0) {
	if (mode_switch)
	    vga_is_gfx = 0;
	return 1;
    }
    sticon_set_origin(c);
    sti_clear(sticon_sti, 0,0, c->vc_rows, c->vc_cols, BLANK);
    if (mode_switch)
	vga_is_gfx = 1;
    return 1;
}