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
struct whc_std {int /*<<< orphan*/  list_node; int /*<<< orphan*/ * qtd; struct urb* urb; } ;
struct whc_qset {int /*<<< orphan*/  stds; } ;
struct whc {int dummy; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct whc_std* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct whc_std *qset_new_std(struct whc *whc, struct whc_qset *qset,
				    struct urb *urb, gfp_t mem_flags)
{
	struct whc_std *std;

	std = kzalloc(sizeof(struct whc_std), mem_flags);
	if (std == NULL)
		return NULL;

	std->urb = urb;
	std->qtd = NULL;

	INIT_LIST_HEAD(&std->list_node);
	list_add_tail(&std->list_node, &qset->stds);

	return std;
}