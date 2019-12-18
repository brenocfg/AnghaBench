#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  nodePool; int /*<<< orphan*/  frame; int /*<<< orphan*/  (* leq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ DictNode ;
typedef  int /*<<< orphan*/ * DictKey ;
typedef  TYPE_2__ Dict ;

/* Variables and functions */
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

DictNode *dictInsertBefore( Dict *dict, DictNode *node, DictKey key )
{
	DictNode *newNode;

	do {
		node = node->prev;
	} while( node->key != NULL && ! (*dict->leq)(dict->frame, node->key, key));

	newNode = (DictNode *)bucketAlloc( dict->nodePool );
	if (newNode == NULL) return NULL;

	newNode->key = key;
	newNode->next = node->next;
	node->next->prev = newNode;
	newNode->prev = node;
	node->next = newNode;

	return newNode;
}