#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  PasswordRemoteOnly; int /*<<< orphan*/  EncryptedPassword; } ;
struct TYPE_7__ {char* Password; int /*<<< orphan*/  PasswordRemoteOnly; } ;
typedef  TYPE_1__ RPC_CLIENT_PASSWORD ;
typedef  TYPE_2__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLog (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  CiSaveConfigurationFile (TYPE_2__*) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmp (char*,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

bool CtSetPassword(CLIENT *c, RPC_CLIENT_PASSWORD *pass)
{
	char *str;
	if (c == NULL)
	{
		return false;
	}

	str = pass->Password;

	if (StrCmp(str, "********") != 0)
	{
		// Hash the password
		Sha0(c->EncryptedPassword, str, StrLen(str));
	}

	c->PasswordRemoteOnly = pass->PasswordRemoteOnly;

	CLog(c, "LC_SET_PASSWORD");

	CiSaveConfigurationFile(c);

	return true;
}