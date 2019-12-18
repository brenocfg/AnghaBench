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
struct ed {struct td* td_head; int /*<<< orphan*/  td_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void fhci_add_tds_to_ed(struct ed *ed, struct td **td_list, int number)
{
	int i;

	for (i = 0; i < number; i++) {
		struct td *td = td_list[i];
		list_add_tail(&td->node, &ed->td_list);
	}
	if (ed->td_head == NULL)
		ed->td_head = td_list[0];
}