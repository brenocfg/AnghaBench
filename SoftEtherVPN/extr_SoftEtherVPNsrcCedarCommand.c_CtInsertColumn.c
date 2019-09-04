#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_7__ {int /*<<< orphan*/  Columns; } ;
struct TYPE_6__ {int Right; int /*<<< orphan*/  String; } ;
typedef  TYPE_1__ CTC ;
typedef  TYPE_2__ CT ;

/* Variables and functions */
 int /*<<< orphan*/  CopyUniStr (char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void CtInsertColumn(CT *ct, wchar_t *str, bool right)
{
	CTC *ctc;
	// Validate arguments
	if (ct == NULL)
	{
		return;
	}
	if (str == NULL)
	{
		str = L"";
	}

	ctc = ZeroMalloc(sizeof(CTC));
	ctc->String = CopyUniStr(str);
	ctc->Right = right;

	Insert(ct->Columns, ctc);
}