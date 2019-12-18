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
struct ehci_qh {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  qh_destroy (struct ehci_qh*) ; 

__attribute__((used)) static inline void qh_put (struct ehci_qh *qh)
{
	if (!--qh->refcount)
		qh_destroy(qh);
}