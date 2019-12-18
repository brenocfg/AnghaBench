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
struct TYPE_4__ {struct TYPE_4__* _matches; struct TYPE_4__* _jmpbuf; struct TYPE_4__* _nodes; } ;
typedef  TYPE_1__ TRex ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void trex_free(TRex *exp)
{
	if(exp)	{
		if(exp->_nodes) free(exp->_nodes);
		if(exp->_jmpbuf) free(exp->_jmpbuf);
		if(exp->_matches) free(exp->_matches);
		free(exp);
	}
}