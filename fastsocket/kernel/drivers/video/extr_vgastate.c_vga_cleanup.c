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
struct vgastate {int /*<<< orphan*/ * vidstate; } ;
struct regstate {int /*<<< orphan*/  attr; int /*<<< orphan*/  vga_cmap; int /*<<< orphan*/  vga_text; int /*<<< orphan*/  vga_font1; int /*<<< orphan*/  vga_font0; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct regstate*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vga_cleanup(struct vgastate *state)
{
	if (state->vidstate != NULL) {
		struct regstate *saved = (struct regstate *) state->vidstate;

		vfree(saved->vga_font0);
		vfree(saved->vga_font1);
		vfree(saved->vga_text);
		vfree(saved->vga_cmap);
		vfree(saved->attr);
		kfree(saved);
		state->vidstate = NULL;
	}
}