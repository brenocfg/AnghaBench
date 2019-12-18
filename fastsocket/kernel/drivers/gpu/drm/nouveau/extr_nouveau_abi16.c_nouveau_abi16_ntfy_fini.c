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
struct nouveau_abi16_ntfy {int /*<<< orphan*/  head; int /*<<< orphan*/  node; } ;
struct nouveau_abi16_chan {int /*<<< orphan*/  heap; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nouveau_abi16_ntfy*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_mm_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nouveau_abi16_ntfy_fini(struct nouveau_abi16_chan *chan,
			struct nouveau_abi16_ntfy *ntfy)
{
	nouveau_mm_free(&chan->heap, &ntfy->node);
	list_del(&ntfy->head);
	kfree(ntfy);
}