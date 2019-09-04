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
struct TYPE_7__ {char* (* ReadPassword ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  K ;
typedef  TYPE_1__ CONSOLE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToK (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsBase64 (int /*<<< orphan*/ *) ; 
 int IsEncryptedK (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ReadDumpW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ) ; 

K *CmdLoadKey(CONSOLE *c, wchar_t *filename)
{
	BUF *b;
	// Validate arguments
	if (c == NULL || filename == NULL)
	{
		return NULL;
	}

	b = ReadDumpW(filename);
	if (b == NULL)
	{
		c->Write(c, _UU("CMD_LOADCERT_FAILED"));
		return NULL;
	}
	else
	{
		K *key;
		if (IsEncryptedK(b, true) == false)
		{
			key = BufToK(b, true, IsBase64(b), NULL);
		}
		else
		{
			c->Write(c, _UU("CMD_LOADKEY_ENCRYPTED_1"));

			while (true)
			{
				char *pass = c->ReadPassword(c, _UU("CMD_LOADKEY_ENCRYPTED_2"));

				if (pass == NULL)
				{
					FreeBuf(b);
					return NULL;
				}

				key = BufToK(b, true, IsBase64(b), pass);
				Free(pass);

				if (key != NULL)
				{
					break;
				}

				c->Write(c, _UU("CMD_LOADKEY_ENCRYPTED_3"));
			}
		}

		FreeBuf(b);

		return key;
	}
}