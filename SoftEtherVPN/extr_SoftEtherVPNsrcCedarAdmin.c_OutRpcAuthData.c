#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_12__ {int /*<<< orphan*/ * NtUsername; } ;
struct TYPE_11__ {int /*<<< orphan*/  NtLmSecureHash; int /*<<< orphan*/  HashedKey; } ;
struct TYPE_10__ {int /*<<< orphan*/ * RadiusUsername; } ;
struct TYPE_9__ {int /*<<< orphan*/ * CommonName; TYPE_1__* Serial; } ;
struct TYPE_8__ {int /*<<< orphan*/  UserX; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ AUTHUSERCERT ;
typedef  TYPE_3__ AUTHROOTCERT ;
typedef  TYPE_4__ AUTHRADIUS ;
typedef  TYPE_5__ AUTHPASSWORD ;
typedef  TYPE_6__ AUTHNT ;

/* Variables and functions */
#define  AUTHTYPE_NT 132 
#define  AUTHTYPE_PASSWORD 131 
#define  AUTHTYPE_RADIUS 130 
#define  AUTHTYPE_ROOTCERT 129 
#define  AUTHTYPE_USERCERT 128 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddX (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcAuthData(PACK *p, void *authdata, UINT authtype)
{
	AUTHPASSWORD *pw = authdata;
	AUTHUSERCERT *usercert = authdata;
	AUTHROOTCERT *rootcert = authdata;
	AUTHRADIUS *radius = authdata;
	AUTHNT *nt = authdata;
	// Validate arguments
	if (p == NULL)
	{
		return;
	}

	PackAddInt(p, "AuthType", authtype);

	switch (authtype)
	{
	case AUTHTYPE_PASSWORD:
		PackAddData(p, "HashedKey", pw->HashedKey, sizeof(pw->HashedKey));
		PackAddData(p, "NtLmSecureHash", pw->NtLmSecureHash, sizeof(pw->NtLmSecureHash));
		break;

	case AUTHTYPE_USERCERT:
		PackAddX(p, "UserX", usercert->UserX);
		break;

	case AUTHTYPE_ROOTCERT:
		if (rootcert->Serial != NULL)
		{
			PackAddData(p, "Serial", rootcert->Serial->data, rootcert->Serial->size);
		}
		if (rootcert->CommonName != NULL)
		{
			PackAddUniStr(p, "CommonName", rootcert->CommonName);
		}
		break;

	case AUTHTYPE_RADIUS:
		PackAddUniStr(p, "RadiusUsername", radius->RadiusUsername);
		break;

	case AUTHTYPE_NT:
		PackAddUniStr(p, "NtUsername", nt->NtUsername);
		break;
	}
}