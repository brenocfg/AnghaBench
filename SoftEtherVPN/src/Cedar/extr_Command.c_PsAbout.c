#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int /*<<< orphan*/  Buf; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,char*) ;} ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ CONSOLE ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintAbout (TYPE_1__*) ; 
 char* CopyUtfToUni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_1__*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ReadDump (char*) ; 
 int /*<<< orphan*/  SeekBufToEnd (TYPE_2__*) ; 
 int /*<<< orphan*/  WriteBufChar (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,char*) ; 

UINT PsAbout(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	BUF *b;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	b = ReadDump("|legal.txt");

	CmdPrintAbout(c);
	c->Write(c, L"\r\n");

	if (b != NULL)
	{
		wchar_t *s;

		SeekBufToEnd(b);
		WriteBufChar(b, 13);
		WriteBufChar(b, 10);
		WriteBufChar(b, 0);

		s = CopyUtfToUni(b->Buf);

		c->Write(c, s);

		Free(s);
	}

	// Display the version information
	c->Write(c, _UU("D_ABOUT@S_INFO3"));
	c->Write(c, L"\r\n");
	c->Write(c, _UU("D_ABOUT@S_INFO4"));
	c->Write(c, L"\r\n");
	CmdPrintAbout(c);
	c->Write(c, L"\r\n");

	FreeParamValueList(o);

	FreeBuf(b);

	return 0;
}