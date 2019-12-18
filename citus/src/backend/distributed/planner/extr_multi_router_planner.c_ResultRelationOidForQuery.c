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
struct TYPE_6__ {int /*<<< orphan*/  rtable; int /*<<< orphan*/  resultRelation; } ;
struct TYPE_5__ {int /*<<< orphan*/  relid; } ;
typedef  TYPE_1__ RangeTblEntry ;
typedef  TYPE_2__ Query ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 TYPE_1__* rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
ResultRelationOidForQuery(Query *query)
{
	RangeTblEntry *resultRTE = rt_fetch(query->resultRelation, query->rtable);

	return resultRTE->relid;
}