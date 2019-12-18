#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ VarLevelsUpWalkerContext ;
typedef  int /*<<< orphan*/  Query ;

/* Variables and functions */
 int /*<<< orphan*/  ContainsReferencesToOuterQueryWalker ; 
 int query_tree_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static bool
ContainsReferencesToOuterQuery(Query *query)
{
	VarLevelsUpWalkerContext context = { 0 };
	int flags = 0;

	return query_tree_walker(query, ContainsReferencesToOuterQueryWalker,
							 &context, flags);
}