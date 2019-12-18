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
struct nouveau_object {int dummy; } ;
struct nouveau_disp {int /*<<< orphan*/  base; int /*<<< orphan*/  vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_engine_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_event_destroy (int /*<<< orphan*/ *) ; 

void
_nouveau_disp_dtor(struct nouveau_object *object)
{
	struct nouveau_disp *disp = (void *)object;
	nouveau_event_destroy(&disp->vblank);
	nouveau_engine_destroy(&disp->base);
}