#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_5__ {TYPE_1__* rd_rel; int /*<<< orphan*/  rd_att; } ;
struct TYPE_4__ {int /*<<< orphan*/  relkind; } ;
typedef  int /*<<< orphan*/  RelationData ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  FormData_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  RELKIND_RELATION ; 
 void* palloc0 (int) ; 

__attribute__((used)) static Relation
StubRelation(TupleDesc tupleDescriptor)
{
	Relation stubRelation = palloc0(sizeof(RelationData));
	stubRelation->rd_att = tupleDescriptor;
	stubRelation->rd_rel = palloc0(sizeof(FormData_pg_class));
	stubRelation->rd_rel->relkind = RELKIND_RELATION;

	return stubRelation;
}