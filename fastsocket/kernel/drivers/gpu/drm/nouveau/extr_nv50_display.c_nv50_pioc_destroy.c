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
struct nv50_pioc {int /*<<< orphan*/  base; } ;
struct nouveau_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nv50_chan_destroy (struct nouveau_object*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nv50_pioc_destroy(struct nouveau_object *core, struct nv50_pioc *pioc)
{
	nv50_chan_destroy(core, &pioc->base);
}