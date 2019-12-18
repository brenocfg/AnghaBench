#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_8__ {void* NtUsername; } ;
struct TYPE_7__ {void* RadiusUsername; } ;
struct TYPE_6__ {void* CommonName; int /*<<< orphan*/ * Serial; } ;
struct TYPE_5__ {int /*<<< orphan*/  UserX; } ;
typedef  TYPE_1__ AUTHUSERCERT ;
typedef  TYPE_2__ AUTHROOTCERT ;
typedef  TYPE_3__ AUTHRADIUS ;
typedef  int /*<<< orphan*/  AUTHPASSWORD ;
typedef  TYPE_4__ AUTHNT ;

/* Variables and functions */
 int AUTHTYPE_ANONYMOUS ; 
#define  AUTHTYPE_NT 132 
#define  AUTHTYPE_PASSWORD 131 
#define  AUTHTYPE_RADIUS 130 
#define  AUTHTYPE_ROOTCERT 129 
#define  AUTHTYPE_USERCERT 128 
 int /*<<< orphan*/  Free (void*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeXSerial (int /*<<< orphan*/ *) ; 

void FreeAuthData(UINT authtype, void *authdata)
{
	AUTHPASSWORD *pw = (AUTHPASSWORD *)authdata;
	AUTHUSERCERT *uc = (AUTHUSERCERT *)authdata;
	AUTHROOTCERT *rc = (AUTHROOTCERT *)authdata;
	AUTHRADIUS *rd = (AUTHRADIUS *)authdata;
	AUTHNT *nt = (AUTHNT *)authdata;
	// Validate arguments
	if (authtype == AUTHTYPE_ANONYMOUS || authdata == NULL)
	{
		return;
	}

	switch (authtype)
	{
	case AUTHTYPE_PASSWORD:
		// Password authentication
		// Nothing to free
		break;

	case AUTHTYPE_USERCERT:
		// User certification
		FreeX(uc->UserX);
		break;

	case AUTHTYPE_ROOTCERT:
		// Root certification
		if (rc->Serial != NULL)
		{
			FreeXSerial(rc->Serial);
		}
		if (rc->CommonName != NULL)
		{
			Free(rc->CommonName);
		}
		break;

	case AUTHTYPE_RADIUS:
		// Radius authentication
		Free(rd->RadiusUsername);
		break;

	case AUTHTYPE_NT:
		// Windows NT authentication
		Free(nt->NtUsername);
		break;
	}

	Free(authdata);
}