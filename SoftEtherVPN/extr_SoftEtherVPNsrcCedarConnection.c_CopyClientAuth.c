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
struct TYPE_5__ {int AuthType; int /*<<< orphan*/  SecurePrivateKeyName; int /*<<< orphan*/  SecurePublicCertName; int /*<<< orphan*/  ClientK; int /*<<< orphan*/  ClientX; int /*<<< orphan*/  PlainPassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  Username; } ;
typedef  TYPE_1__ CLIENT_AUTH ;

/* Variables and functions */
#define  CLIENT_AUTHTYPE_ANONYMOUS 132 
#define  CLIENT_AUTHTYPE_CERT 131 
#define  CLIENT_AUTHTYPE_PASSWORD 130 
#define  CLIENT_AUTHTYPE_PLAIN_PASSWORD 129 
#define  CLIENT_AUTHTYPE_SECURE 128 
 int /*<<< orphan*/  CloneK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloneX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMallocEx (int,int) ; 

CLIENT_AUTH *CopyClientAuth(CLIENT_AUTH *a)
{
	CLIENT_AUTH *ret;
	// Validate arguments
	if (a == NULL)
	{
		return NULL;
	}

	ret = ZeroMallocEx(sizeof(CLIENT_AUTH), true);

	ret->AuthType = a->AuthType;
	StrCpy(ret->Username, sizeof(ret->Username), a->Username);

	switch (a->AuthType)
	{
	case CLIENT_AUTHTYPE_ANONYMOUS:
		// Anonymous authentication
		break;

	case CLIENT_AUTHTYPE_PASSWORD:
		// Password authentication
		Copy(ret->HashedPassword, a->HashedPassword, SHA1_SIZE);
		break;

	case CLIENT_AUTHTYPE_PLAIN_PASSWORD:
		// Plaintext password authentication
		StrCpy(ret->PlainPassword, sizeof(ret->PlainPassword), a->PlainPassword);
		break;

	case CLIENT_AUTHTYPE_CERT:
		// Certificate authentication
		ret->ClientX = CloneX(a->ClientX);
		ret->ClientK = CloneK(a->ClientK);
		break;

	case CLIENT_AUTHTYPE_SECURE:
		// Secure device authentication
		StrCpy(ret->SecurePublicCertName, sizeof(ret->SecurePublicCertName), a->SecurePublicCertName);
		StrCpy(ret->SecurePrivateKeyName, sizeof(ret->SecurePrivateKeyName), a->SecurePrivateKeyName);
		break;
	}

	return ret;
}