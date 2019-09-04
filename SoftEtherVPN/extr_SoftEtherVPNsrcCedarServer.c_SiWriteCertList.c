#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ *,int) ; 

void SiWriteCertList(FOLDER *f, LIST *o)
{
	// Validate arguments
	if (f == NULL || o == NULL)
	{
		return;
	}

	LockList(o);
	{
		UINT i;
		X *x;
		for (i = 0;i < LIST_NUM(o);i++)
		{
			char name[MAX_SIZE];
			BUF *b;
			x = LIST_DATA(o, i);
			Format(name, sizeof(name), "Cert%u", i);
			b = XToBuf(x, false);
			if (b != NULL)
			{
				CfgAddBuf(CfgCreateFolder(f, name), "X509", b);
				FreeBuf(b);
			}
		}
	}
	UnlockList(o);
}