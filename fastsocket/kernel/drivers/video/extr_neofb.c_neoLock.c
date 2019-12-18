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
struct vgastate {int /*<<< orphan*/  vgabase; } ;

/* Variables and functions */
 int /*<<< orphan*/  vgaHWLock (struct vgastate*) ; 
 int /*<<< orphan*/  vga_wgfx (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void neoLock(struct vgastate *state)
{
	vga_wgfx(state->vgabase, 0x09, 0x00);
	vgaHWLock(state);
}