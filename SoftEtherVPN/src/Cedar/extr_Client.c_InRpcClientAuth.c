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
struct TYPE_4__ {int AuthType; int /*<<< orphan*/  SecurePrivateKeyName; int /*<<< orphan*/  SecurePublicCertName; int /*<<< orphan*/  ClientK; int /*<<< orphan*/  ClientX; int /*<<< orphan*/  PlainPassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  Username; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CLIENT_AUTH ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  BufToK (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BufToX (int /*<<< orphan*/ *,int) ; 
#define  CLIENT_AUTHTYPE_ANONYMOUS 132 
#define  CLIENT_AUTHTYPE_CERT 131 
#define  CLIENT_AUTHTYPE_PASSWORD 130 
#define  CLIENT_AUTHTYPE_PLAIN_PASSWORD 129 
#define  CLIENT_AUTHTYPE_SECURE 128 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 int PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientAuth(CLIENT_AUTH *c, PACK *p)
{
	BUF *b;
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	Zero(c, sizeof(CLIENT_AUTH));
	c->AuthType = PackGetInt(p, "AuthType");
	PackGetStr(p, "Username", c->Username, sizeof(c->Username));

	switch (c->AuthType)
	{
	case CLIENT_AUTHTYPE_ANONYMOUS:
		break;

	case CLIENT_AUTHTYPE_PASSWORD:
		if (PackGetDataSize(p, "HashedPassword") == SHA1_SIZE)
		{
			PackGetData(p, "HashedPassword", c->HashedPassword);
		}
		break;

	case CLIENT_AUTHTYPE_PLAIN_PASSWORD:
		PackGetStr(p, "PlainPassword", c->PlainPassword, sizeof(c->PlainPassword));
		break;

	case CLIENT_AUTHTYPE_CERT:
		b = PackGetBuf(p, "ClientX");
		if (b != NULL)
		{
			c->ClientX = BufToX(b, false);
			FreeBuf(b);
		}
		b = PackGetBuf(p, "ClientK");
		if (b != NULL)
		{
			c->ClientK = BufToK(b, true, false, NULL);
			FreeBuf(b);
		}
		break;

	case CLIENT_AUTHTYPE_SECURE:
		PackGetStr(p, "SecurePublicCertName", c->SecurePublicCertName, sizeof(c->SecurePublicCertName));
		PackGetStr(p, "SecurePrivateKeyName", c->SecurePrivateKeyName, sizeof(c->SecurePrivateKeyName));
		break;
	}
}