#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_8__ {int AuthType; int /*<<< orphan*/  SecurePrivateKeyName; int /*<<< orphan*/  SecurePublicCertName; int /*<<< orphan*/ * ClientK; int /*<<< orphan*/ * ClientX; int /*<<< orphan*/  PlainPassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  Username; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT_AUTH ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
#define  CLIENT_AUTHTYPE_ANONYMOUS 132 
#define  CLIENT_AUTHTYPE_CERT 131 
#define  CLIENT_AUTHTYPE_PASSWORD 130 
#define  CLIENT_AUTHTYPE_PLAIN_PASSWORD 129 
#define  CLIENT_AUTHTYPE_SECURE 128 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* EncryptPassword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* KToBuf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 TYPE_2__* XToBuf (int /*<<< orphan*/ *,int) ; 

void CiWriteClientAuth(FOLDER *f, CLIENT_AUTH *a)
{
	BUF *b;
	// Validate arguments
	if (f == NULL || a == NULL)
	{
		return;
	}

	CfgAddInt(f, "AuthType", a->AuthType);
	CfgAddStr(f, "Username", a->Username);

	switch (a->AuthType)
	{
	case CLIENT_AUTHTYPE_ANONYMOUS:
		break;

	case CLIENT_AUTHTYPE_PASSWORD:
		CfgAddByte(f, "HashedPassword", a->HashedPassword, SHA1_SIZE);
		break;

	case CLIENT_AUTHTYPE_PLAIN_PASSWORD:
		b = EncryptPassword(a->PlainPassword);
		CfgAddByte(f, "EncryptedPassword", b->Buf, b->Size);
		FreeBuf(b);
		break;

	case CLIENT_AUTHTYPE_CERT:
		if (a->ClientK != NULL && a->ClientX != NULL)
		{
			b = XToBuf(a->ClientX, false);
			CfgAddByte(f, "ClientCert", b->Buf, b->Size);
			FreeBuf(b);

			b = KToBuf(a->ClientK, false, NULL);
			CfgAddByte(f, "ClientKey", b->Buf, b->Size);
			FreeBuf(b);
		}
		break;

	case CLIENT_AUTHTYPE_SECURE:
		CfgAddStr(f, "SecurePublicCertName", a->SecurePublicCertName);
		CfgAddStr(f, "SecurePrivateKeyName", a->SecurePrivateKeyName);
		break;
	}
}