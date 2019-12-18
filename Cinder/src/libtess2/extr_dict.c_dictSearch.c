#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/ * key; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  (* leq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__ head; } ;
typedef  TYPE_1__ DictNode ;
typedef  int /*<<< orphan*/  DictKey ;
typedef  TYPE_2__ Dict ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

DictNode *dictSearch( Dict *dict, DictKey key )
{
	DictNode *node = &dict->head;

	do {
		node = node->next;
	} while( node->key != NULL && ! (*dict->leq)(dict->frame, key, node->key));

	return node;
}