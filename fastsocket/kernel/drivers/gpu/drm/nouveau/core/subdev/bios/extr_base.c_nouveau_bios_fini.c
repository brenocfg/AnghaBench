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
struct nouveau_bios {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int nouveau_subdev_fini (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
nouveau_bios_fini(struct nouveau_object *object, bool suspend)
{
	struct nouveau_bios *bios = (void *)object;
	return nouveau_subdev_fini(&bios->base, suspend);
}