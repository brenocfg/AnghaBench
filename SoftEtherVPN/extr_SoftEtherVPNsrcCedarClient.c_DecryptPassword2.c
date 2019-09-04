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
struct TYPE_3__ {int Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  CRYPT ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Encrypt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeCrypt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewCrypt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 char* ZeroMalloc (int) ; 

char *DecryptPassword2(BUF *b)
{
	char *str;
	char *key = "EncryptPassword2";
	CRYPT *c;
	// Validate arguments
	if (b == NULL)
	{
		return CopyStr("");
	}

	str = ZeroMalloc(b->Size + 1);
	c = NewCrypt(key, StrLen(key));
	Encrypt(c, str, b->Buf, b->Size);
	FreeCrypt(c);

	str[b->Size] = 0;

	return str;
}