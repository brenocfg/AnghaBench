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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  CheckCitusVersion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CitusHasBeenLoaded () ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  OverrideTableVisibility ; 
 int /*<<< orphan*/  ReplaceTableVisibleFunctionWalker (int /*<<< orphan*/ *) ; 

void
ReplaceTableVisibleFunction(Node *inputNode)
{
	if (!OverrideTableVisibility ||
		!CitusHasBeenLoaded() || !CheckCitusVersion(DEBUG2))
	{
		return;
	}

	ReplaceTableVisibleFunctionWalker(inputNode);
}