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
typedef  int /*<<< orphan*/  FOLDER ;
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
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 char* DecryptPassword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

CLIENT_AUTH *CiLoadClientAuth(FOLDER *f)
{
	CLIENT_AUTH *a;
	char *s;
	BUF *b;
	// Validate arguments
	if (f == NULL)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(CLIENT_AUTH));

	a->AuthType = CfgGetInt(f, "AuthType");
	CfgGetStr(f, "Username", a->Username, sizeof(a->Username));

	switch (a->AuthType)
	{
	case CLIENT_AUTHTYPE_ANONYMOUS:
		break;

	case CLIENT_AUTHTYPE_PASSWORD:
		CfgGetByte(f, "HashedPassword", a->HashedPassword, SHA1_SIZE);
		break;

	case CLIENT_AUTHTYPE_PLAIN_PASSWORD:
		b = CfgGetBuf(f, "EncryptedPassword");
		if (b != NULL)
		{
			s = DecryptPassword(b);
			StrCpy(a->PlainPassword, sizeof(a->PlainPassword), s);
			Free(s);
			FreeBuf(b);
		}
		break;

	case CLIENT_AUTHTYPE_CERT:
		b = CfgGetBuf(f, "ClientCert");
		if (b != NULL)
		{
			a->ClientX = BufToX(b, false);
		}
		FreeBuf(b);
		b = CfgGetBuf(f, "ClientKey");
		if (b != NULL)
		{
			a->ClientK = BufToK(b, true, false, NULL);
		}
		FreeBuf(b);
		break;

	case CLIENT_AUTHTYPE_SECURE:
		CfgGetStr(f, "SecurePublicCertName", a->SecurePublicCertName, sizeof(a->SecurePublicCertName));
		CfgGetStr(f, "SecurePrivateKeyName", a->SecurePrivateKeyName, sizeof(a->SecurePrivateKeyName));
		break;
	}

	return a;
}