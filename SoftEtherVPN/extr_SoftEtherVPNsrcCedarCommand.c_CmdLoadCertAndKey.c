#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  X ;
struct TYPE_7__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 int CheckXandK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CmdLoadKey (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileToXW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 

bool CmdLoadCertAndKey(CONSOLE *c, X **xx, K **kk, wchar_t *cert_filename, wchar_t *key_filename)
{
	X *x;
	K *k;
	// Validate arguments
	if (c == NULL || cert_filename == NULL || key_filename == NULL || xx == NULL || kk == NULL)
	{
		return false;
	}

	x = FileToXW(cert_filename);
	if (x == NULL)
	{
		c->Write(c, _UU("CMD_LOADCERT_FAILED"));
		return false;
	}

	k = CmdLoadKey(c, key_filename);
	if (k == NULL)
	{
		c->Write(c, _UU("CMD_LOADKEY_FAILED"));
		FreeX(x);
		return false;
	}

	if (CheckXandK(x, k) == false)
	{
		c->Write(c, _UU("CMD_KEYPAIR_FAILED"));
		FreeX(x);
		FreeK(k);

		return false;
	}

	*xx = x;
	*kk = k;

	return true;
}