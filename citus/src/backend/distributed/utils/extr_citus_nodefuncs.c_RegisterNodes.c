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

/* Variables and functions */
 int /*<<< orphan*/ * CitusNodeTagNamesD ; 
 int /*<<< orphan*/  RegisterExtensibleNodeMethods (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StaticAssertExpr (int,char*) ; 
 int lengthof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nodeMethods ; 

void
RegisterNodes(void)
{
	int off;

	StaticAssertExpr(lengthof(nodeMethods) == lengthof(CitusNodeTagNamesD),
					 "number of node methods and names do not match");

	for (off = 0; off < lengthof(nodeMethods); off++)
	{
		RegisterExtensibleNodeMethods(&nodeMethods[off]);
	}
}