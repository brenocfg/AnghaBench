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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  CRYPT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCrypt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/ * NewCrypt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  WriteBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ZeroMalloc (scalar_t__) ; 

BUF *EncryptPassword2(char *password)
{
	UCHAR *tmp;
	UINT size;
	char *key = "EncryptPassword2";
	CRYPT *c;
	BUF *b;
	// Validate arguments
	if (password == NULL)
	{
		password = "";
	}

	size = StrLen(password) + 1;
	tmp = ZeroMalloc(size);

	c = NewCrypt(key, StrLen(key));
	Encrypt(c, tmp, password, size - 1);
	FreeCrypt(c);

	b = NewBuf();
	WriteBuf(b, tmp, size - 1);
	SeekBuf(b, 0, 0);
	Free(tmp);

	return b;
}