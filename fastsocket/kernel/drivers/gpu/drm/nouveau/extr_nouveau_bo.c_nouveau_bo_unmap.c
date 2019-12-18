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
struct nouveau_bo {int /*<<< orphan*/  kmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_kunmap (int /*<<< orphan*/ *) ; 

void
nouveau_bo_unmap(struct nouveau_bo *nvbo)
{
	if (nvbo)
		ttm_bo_kunmap(&nvbo->kmap);
}