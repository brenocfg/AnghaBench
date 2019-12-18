#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  cn ;
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  NAME ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDaysUntil2038Ex () ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewRootX (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RsaGen (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 

void SiGenerateDefaultCertEx(X **server_x, K **server_k, char *common_name)
{
	X *x;
	K *private_key, *public_key;
	NAME *name;
	char tmp[MAX_SIZE];
	wchar_t cn[MAX_SIZE];
	// Validate arguments
	if (server_x == NULL || server_k == NULL)
	{
		return;
	}

	// Create a key pair
	RsaGen(&private_key, &public_key, 2048);

	if (IsEmptyStr(common_name))
	{
		// Get the host name
		StrCpy(tmp, sizeof(tmp), "server.softether.vpn");
		GetMachineName(tmp, sizeof(tmp));
		StrToUni(cn, sizeof(cn), tmp);
	}
	else
	{
		StrToUni(cn, sizeof(cn), common_name);
	}

	name = NewName(cn, cn, cn,
		L"US", NULL, NULL);
	x = NewRootX(public_key, private_key, name, GetDaysUntil2038Ex(), NULL);

	*server_x = x;
	*server_k = private_key;

	FreeName(name);

	FreeK(public_key);
}