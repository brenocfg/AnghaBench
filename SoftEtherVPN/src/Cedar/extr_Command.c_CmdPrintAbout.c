#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  exe ;
struct TYPE_8__ {int /*<<< orphan*/  BuildInfo; int /*<<< orphan*/  VerString; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ CONSOLE ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetExeName (char*,int) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 TYPE_2__* NewCedar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCedar (TYPE_2__*) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void CmdPrintAbout(CONSOLE *c)
{
	CEDAR *cedar;
	wchar_t tmp[MAX_SIZE];
	char exe[MAX_PATH];
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	cedar = NewCedar(NULL, NULL);

	GetExeName(exe, sizeof(exe));

	UniFormat(tmp, sizeof(tmp), _UU("CMD_VPNCMD_ABOUT"),
		cedar->VerString, cedar->BuildInfo);

	c->Write(c, tmp);

	ReleaseCedar(cedar);
}