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
struct validate_op {int /*<<< orphan*/  both_list; int /*<<< orphan*/  gart_list; int /*<<< orphan*/  vram_list; } ;
struct nouveau_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  validate_fini_list (int /*<<< orphan*/ *,struct nouveau_fence*) ; 

__attribute__((used)) static void
validate_fini(struct validate_op *op, struct nouveau_fence* fence)
{
	validate_fini_list(&op->vram_list, fence);
	validate_fini_list(&op->gart_list, fence);
	validate_fini_list(&op->both_list, fence);
}