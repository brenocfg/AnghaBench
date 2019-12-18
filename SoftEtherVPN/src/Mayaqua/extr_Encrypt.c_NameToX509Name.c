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
typedef  void X509_NAME ;
struct TYPE_3__ {int /*<<< orphan*/  Local; int /*<<< orphan*/  State; int /*<<< orphan*/  Country; int /*<<< orphan*/  Unit; int /*<<< orphan*/  Organization; int /*<<< orphan*/  CommonName; } ;
typedef  TYPE_1__ NAME ;

/* Variables and functions */
 int /*<<< orphan*/  AddX509Name (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_commonName ; 
 int /*<<< orphan*/  NID_countryName ; 
 int /*<<< orphan*/  NID_localityName ; 
 int /*<<< orphan*/  NID_organizationName ; 
 int /*<<< orphan*/  NID_organizationalUnitName ; 
 int /*<<< orphan*/  NID_stateOrProvinceName ; 
 void* X509_NAME_new () ; 

void *NameToX509Name(NAME *nm)
{
	X509_NAME *xn;
	// Validate arguments
	if (nm == NULL)
	{
		return NULL;
	}

	xn = X509_NAME_new();
	if (xn == NULL)
	{
		return NULL;
	}

	// Add the entries
	AddX509Name(xn, NID_commonName, nm->CommonName);
	AddX509Name(xn, NID_organizationName, nm->Organization);
	AddX509Name(xn, NID_organizationalUnitName, nm->Unit);
	AddX509Name(xn, NID_countryName, nm->Country);
	AddX509Name(xn, NID_stateOrProvinceName, nm->State);
	AddX509Name(xn, NID_localityName, nm->Local);

	return xn;
}