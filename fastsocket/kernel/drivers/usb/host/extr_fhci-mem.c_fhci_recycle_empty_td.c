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
struct td {int /*<<< orphan*/  node; } ;
struct fhci_hcd {int /*<<< orphan*/  empty_tds; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_td (struct td*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void fhci_recycle_empty_td(struct fhci_hcd *fhci, struct td *td)
{
	init_td(td);
	list_add(&td->node, &fhci->empty_tds);
}