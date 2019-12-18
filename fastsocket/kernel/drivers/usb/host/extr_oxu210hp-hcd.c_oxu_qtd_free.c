#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct oxu_hcd {int /*<<< orphan*/  mem_lock; scalar_t__* qtd_used; TYPE_1__* mem; } ;
struct ehci_qtd {scalar_t__ buffer; } ;
struct TYPE_2__ {struct ehci_qtd* qtd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  oxu_buf_free (struct oxu_hcd*,struct ehci_qtd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void oxu_qtd_free(struct oxu_hcd *oxu, struct ehci_qtd *qtd)
{
	int index;

	if (qtd->buffer)
		oxu_buf_free(oxu, qtd);

	spin_lock(&oxu->mem_lock);

	index = qtd - &oxu->mem->qtd_pool[0];
	oxu->qtd_used[index] = 0;

	spin_unlock(&oxu->mem_lock);

	return;
}