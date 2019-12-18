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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  MultiBinaryNode ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leftChildNode ; 
 int /*<<< orphan*/  rightChildNode ; 

__attribute__((used)) static void
OutMultiBinaryNodeFields(StringInfo str, const MultiBinaryNode *node)
{
	WRITE_NODE_FIELD(leftChildNode);
	WRITE_NODE_FIELD(rightChildNode);
}