#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int Id; int /*<<< orphan*/  StringA; int /*<<< orphan*/ * String; } ;
typedef  TYPE_1__ VI_STRING ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  HINSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ViCompareString ; 
 int /*<<< orphan*/ * ViLoadString (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  string_table ; 

void ViLoadStringTables()
{
	UINT i, n;
	HINSTANCE hInst = GetModuleHandle(NULL);

	string_table = NewList(ViCompareString);

	n = 0;
	for (i = 1;;i++)
	{
		wchar_t *str = ViLoadString(hInst, i);
		if (str != NULL)
		{
			VI_STRING *s;
			n = 0;

			s = ZeroMalloc(sizeof(VI_STRING));
			s->Id = i;
			s->String = str;
			s->StringA = CopyUniToStr(str);

			Insert(string_table, s);
		}
		else
		{
			n++;
			if (n >= 1500)
			{
				break;
			}
		}
	}
}