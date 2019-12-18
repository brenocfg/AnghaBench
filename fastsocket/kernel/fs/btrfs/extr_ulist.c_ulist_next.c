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
struct ulist_node {int dummy; } ;
struct ulist_iterator {scalar_t__ i; } ;
struct ulist {scalar_t__ nnodes; struct ulist_node* nodes; } ;

/* Variables and functions */

struct ulist_node *ulist_next(struct ulist *ulist, struct ulist_iterator *uiter)
{
	if (ulist->nnodes == 0)
		return NULL;
	if (uiter->i < 0 || uiter->i >= ulist->nnodes)
		return NULL;

	return &ulist->nodes[uiter->i++];
}