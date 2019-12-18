#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/  Sha0 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void HashPassword(void *dst, char *username, char *password)
{
	BUF *b;
	char *username_upper;
	// Validate arguments
	if (dst == NULL || username == NULL || password == NULL)
	{
		return;
	}

	b = NewBuf();
	username_upper = CopyStr(username);
	StrUpper(username_upper);
	WriteBuf(b, password, StrLen(password));
	WriteBuf(b, username_upper, StrLen(username_upper));
	Sha0(dst, b->Buf, b->Size);

	FreeBuf(b);
	Free(username_upper);
}