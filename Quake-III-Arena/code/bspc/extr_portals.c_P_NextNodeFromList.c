#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 TYPE_1__* p_firstnode ; 
 int /*<<< orphan*/ * p_lastnode ; 

node_t *P_NextNodeFromList(void)
{
	node_t *node;

	node = p_firstnode;
	if (p_firstnode) p_firstnode = p_firstnode->next;
	if (!p_firstnode) p_lastnode = NULL;
	return node;
}