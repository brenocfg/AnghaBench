#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* subject_name; int /*<<< orphan*/ * serial; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {TYPE_2__* Name; int /*<<< orphan*/  DigestSHA1; int /*<<< orphan*/  DigestMD5; int /*<<< orphan*/ * Serial; } ;
struct TYPE_8__ {int /*<<< orphan*/ * Local; int /*<<< orphan*/ * State; int /*<<< orphan*/ * Country; int /*<<< orphan*/ * Unit; int /*<<< orphan*/ * Organization; int /*<<< orphan*/ * CommonName; } ;
typedef  TYPE_2__ NAME ;
typedef  TYPE_3__ CRL ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int CompareXSerial (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetXDigest (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int IsZero (int /*<<< orphan*/ ,int) ; 
 int MD5_SIZE ; 
 int SHA1_SIZE ; 
 int UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 scalar_t__ UniSoftStrCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool IsCertMatchCrl(X *x, CRL *crl)
{
	bool b = true;
	// Validate arguments
	if (x == NULL || crl == NULL)
	{
		return false;
	}

	if (crl->Serial != NULL)
	{
		// If a serial number is defined in the CRL
		if (x->serial == NULL || CompareXSerial(x->serial, crl->Serial) == false)
		{
			// Serial number mismatch
			b = false;
		}
	}

	if (IsZero(crl->DigestMD5, sizeof(crl->DigestMD5)) == false)
	{
		UCHAR test[MD5_SIZE];
		// If a DigestMD5 is defined in the CRL
		GetXDigest(x, test, false);

		if (Cmp(test, crl->DigestMD5, MD5_SIZE) != 0)
		{
			b = false;
		}
	}

	if (IsZero(crl->DigestSHA1, sizeof(crl->DigestSHA1)) == false)
	{
		UCHAR test[SHA1_SIZE];
		// If a DigestSHA1 is defined in the CRL
		GetXDigest(x, test, true);

		if (Cmp(test, crl->DigestSHA1, SHA1_SIZE) != 0)
		{
			b = false;
		}
	}

	if (crl->Name != NULL)
	{
		// If a name is defined in the CRL
		NAME *xn, *cn;
		xn = x->subject_name;
		cn = crl->Name;

		if (cn->CommonName != NULL && (UniIsEmptyStr(cn->CommonName) == false))
		{
			if (xn->CommonName == NULL || UniSoftStrCmp(xn->CommonName, cn->CommonName) != 0)
			{
				// CommonName mismatch
				b = false;
			}
		}

		if (cn->Organization != NULL && (UniIsEmptyStr(cn->Organization) == false))
		{
			if (xn->Organization == NULL || UniSoftStrCmp(xn->Organization, cn->Organization) != 0)
			{
				// Organization mismatch
				b = false;
			}
		}

		if (cn->Unit != NULL && (UniIsEmptyStr(cn->Unit) == false))
		{
			if (xn->Unit == NULL || UniSoftStrCmp(xn->Unit, cn->Unit) != 0)
			{
				// Unit mismatch
				b = false;
			}
		}

		if (cn->Country != NULL && (UniIsEmptyStr(cn->Country) == false))
		{
			if (xn->Country == NULL || UniSoftStrCmp(xn->Country, cn->Country) != 0)
			{
				// Country mismatch
				b = false;
			}
		}

		if (cn->State != NULL && (UniIsEmptyStr(cn->State) == false))
		{
			if (xn->State == NULL || UniSoftStrCmp(xn->State, cn->State) != 0)
			{
				// State mismatch
				b = false;
			}
		}

		if (cn->Local != NULL && (UniIsEmptyStr(cn->Local) == false))
		{
			if (xn->Local == NULL || UniSoftStrCmp(xn->Local, cn->Local) != 0)
			{
				// Local mismatch
				b = false;
			}
		}
	}

	return b;
}