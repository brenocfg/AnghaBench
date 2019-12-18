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
typedef  int /*<<< orphan*/  MultiUnaryNode ;
typedef  int /*<<< orphan*/  MultiNode ;
typedef  int /*<<< orphan*/  MultiExtendedOp ;

/* Variables and functions */
 int /*<<< orphan*/ * ChildNode (int /*<<< orphan*/ *) ; 
 scalar_t__ CitusIsA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MultiCollect ; 
 int /*<<< orphan*/  MultiTable ; 
 int /*<<< orphan*/ * ParentNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ExtendedOpNodeContainsRepartitionSubquery(MultiExtendedOp *originalOpNode)
{
	MultiNode *parentNode = ParentNode((MultiNode *) originalOpNode);
	MultiNode *childNode = ChildNode((MultiUnaryNode *) originalOpNode);

	if (CitusIsA(parentNode, MultiTable) && CitusIsA(childNode, MultiCollect))
	{
		return true;
	}

	return false;
}