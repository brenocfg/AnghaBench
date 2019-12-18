#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_10__ {int /*<<< orphan*/  Rows; int /*<<< orphan*/  Columns; } ;
struct TYPE_9__ {char* String; } ;
struct TYPE_8__ {char** Strings; } ;
typedef  TYPE_1__ CTR ;
typedef  TYPE_2__ CTC ;
typedef  TYPE_3__ CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CtFree (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (TYPE_3__*,char*,char*) ; 
 TYPE_3__* CtNewStandard () ; 
 void* LIST_DATA (int /*<<< orphan*/ ,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 

void CtPrintStandard(CT *ct, CONSOLE *c)
{
	CT *t;
	UINT i, j;
	// Validate arguments
	if (ct == NULL || c == NULL)
	{
		return;
	}

	t = CtNewStandard();
	for (i = 0;i < LIST_NUM(ct->Rows);i++)
	{
		CTR *row = LIST_DATA(ct->Rows, i);

		for (j = 0;j < LIST_NUM(ct->Columns);j++)
		{
			CTC *column = LIST_DATA(ct->Columns, j);

			CtInsert(t, column->String, row->Strings[j]);
		}

		if (i != (LIST_NUM(ct->Rows) - 1))
		{
			CtInsert(t, L"---", L"---");
		}
	}

	CtFree(t, c);
}