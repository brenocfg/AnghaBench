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
struct TYPE_3__ {int AuthType; int /*<<< orphan*/  SecurePrivateKeyName; int /*<<< orphan*/  SecurePublicCertName; int /*<<< orphan*/  ClientK; int /*<<< orphan*/  ClientX; int /*<<< orphan*/  PlainPassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  Username; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CLIENT_AUTH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
#define  CLIENT_AUTHTYPE_ANONYMOUS 132 
#define  CLIENT_AUTHTYPE_CERT 131 
#define  CLIENT_AUTHTYPE_PASSWORD 130 
#define  CLIENT_AUTHTYPE_PLAIN_PASSWORD 129 
#define  CLIENT_AUTHTYPE_SECURE 128 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * KToBuf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ ,int) ; 

void OutRpcClientAuth(PACK *p, CLIENT_AUTH *c)
{
	BUF *b;
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "AuthType", c->AuthType);
	PackAddStr(p, "Username", c->Username);

	switch (c->AuthType)
	{
	case CLIENT_AUTHTYPE_ANONYMOUS:
		break;

	case CLIENT_AUTHTYPE_PASSWORD:
		PackAddData(p, "HashedPassword", c->HashedPassword, SHA1_SIZE);
		break;

	case CLIENT_AUTHTYPE_PLAIN_PASSWORD:
		PackAddStr(p, "PlainPassword", c->PlainPassword);
		break;

	case CLIENT_AUTHTYPE_CERT:
		b = XToBuf(c->ClientX, false);
		if (b != NULL)
		{
			PackAddBuf(p, "ClientX", b);
			FreeBuf(b);
		}
		b = KToBuf(c->ClientK, false, NULL);
		if (b != NULL)
		{
			PackAddBuf(p, "ClientK", b);
			FreeBuf(b);
		}
		break;

	case CLIENT_AUTHTYPE_SECURE:
		PackAddStr(p, "SecurePublicCertName", c->SecurePublicCertName);
		PackAddStr(p, "SecurePrivateKeyName", c->SecurePrivateKeyName);
		break;
	}
}