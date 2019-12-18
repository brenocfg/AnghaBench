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
typedef  int /*<<< orphan*/  tnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  InitSurfacesForTesting () ; 
 int MAX_TNODES ; 
 int /*<<< orphan*/  MakeTnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/ * tnode_p ; 
 int /*<<< orphan*/ * tnodes ; 

void InitTrace( void ) {
	// 32 byte align the structs
	tnodes = malloc( (MAX_TNODES+1) * sizeof(tnode_t));
	tnodes = (tnode_t *)(((int)tnodes + 31)&~31);
	tnode_p = tnodes;

	MakeTnode (0);

	InitSurfacesForTesting();
}