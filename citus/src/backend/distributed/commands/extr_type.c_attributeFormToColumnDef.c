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
struct TYPE_3__ {int /*<<< orphan*/  attcollation; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; } ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  ColumnDef ;

/* Variables and functions */
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeColumnDef (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ColumnDef *
attributeFormToColumnDef(Form_pg_attribute attributeForm)
{
	return makeColumnDef(NameStr(attributeForm->attname),
						 attributeForm->atttypid,
						 -1,
						 attributeForm->attcollation);
}