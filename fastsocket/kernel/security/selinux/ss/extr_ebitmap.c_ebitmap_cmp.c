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
struct ebitmap_node {scalar_t__ startbit; struct ebitmap_node* next; int /*<<< orphan*/  maps; } ;
struct ebitmap {scalar_t__ highbit; struct ebitmap_node* node; } ;

/* Variables and functions */
 int EBITMAP_SIZE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ebitmap_cmp(struct ebitmap *e1, struct ebitmap *e2)
{
	struct ebitmap_node *n1, *n2;

	if (e1->highbit != e2->highbit)
		return 0;

	n1 = e1->node;
	n2 = e2->node;
	while (n1 && n2 &&
	       (n1->startbit == n2->startbit) &&
	       !memcmp(n1->maps, n2->maps, EBITMAP_SIZE / 8)) {
		n1 = n1->next;
		n2 = n2->next;
	}

	if (n1 || n2)
		return 0;

	return 1;
}