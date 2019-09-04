#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct affinity_set {int dummy; } ;
typedef  TYPE_1__* affinity_set_t ;
struct TYPE_5__ {int /*<<< orphan*/  aset_threads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 
 int /*<<< orphan*/  queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
affinity_set_free(affinity_set_t aset)
{
	assert(queue_empty(&aset->aset_threads));

	DBG("affinity_set_free(%p)\n", aset);
	kfree(aset, sizeof(struct affinity_set));
}