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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {void* Buf; int /*<<< orphan*/  Size; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_AUTHTYPE_CERT ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_1__* XToBuf (int /*<<< orphan*/ *,int) ; 

PACK *PackLoginWithCert(char *hubname, char *username, X *x, void *sign, UINT sign_size)
{
	PACK *p;
	BUF *b;
	// Validate arguments
	if (hubname == NULL || username == NULL)
	{
		return NULL;
	}

	p = NewPack();
	PackAddStr(p, "method", "login");
	PackAddStr(p, "hubname", hubname);
	PackAddStr(p, "username", username);
	PackAddInt(p, "authtype", CLIENT_AUTHTYPE_CERT);

	// Certificate
	b = XToBuf(x, false);
	PackAddData(p, "cert", b->Buf, b->Size);
	FreeBuf(b);

	// Signature data
	PackAddData(p, "sign", sign, sign_size);

	return p;
}