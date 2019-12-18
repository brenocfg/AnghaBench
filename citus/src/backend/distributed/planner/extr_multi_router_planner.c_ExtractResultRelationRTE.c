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
struct TYPE_3__ {int /*<<< orphan*/  rtable; int /*<<< orphan*/  resultRelation; } ;
typedef  int /*<<< orphan*/  RangeTblEntry ;
typedef  TYPE_1__ Query ;

/* Variables and functions */
 int /*<<< orphan*/ * rt_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RangeTblEntry *
ExtractResultRelationRTE(Query *query)
{
	return rt_fetch(query->resultRelation, query->rtable);
}