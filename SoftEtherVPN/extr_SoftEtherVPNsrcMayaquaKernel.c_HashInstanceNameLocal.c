#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {scalar_t__ OsType; } ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Format (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int GET_KETA (scalar_t__,int) ; 
 TYPE_1__* GetOsInfo () ; 
 int MAX_SIZE ; 
 scalar_t__ OSTYPE_WINDOWS_NT_4_TERMINAL_SERVER ; 
 scalar_t__ OS_IS_WINDOWS_NT (scalar_t__) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

void HashInstanceNameLocal(char *name, UINT size, char *instance_name)
{
	char tmp[MAX_SIZE];
	UCHAR hash[SHA1_SIZE];
	char key[11];
	// Validate arguments
	if (name == NULL || instance_name == NULL)
	{
		return;
	}

	StrCpy(tmp, sizeof(tmp), instance_name);
	Trim(tmp);
	StrUpper(tmp);

	Sha0(hash, tmp, StrLen(tmp));
	BinToStr(key, sizeof(key), hash, 5);
	key[10] = 0;

	Format(name, size, "VPN-%s", key);

	if (OS_IS_WINDOWS_NT(GetOsInfo()->OsType))
	{
		if (GET_KETA(GetOsInfo()->OsType, 100) >= 2 ||
			GetOsInfo()->OsType == OSTYPE_WINDOWS_NT_4_TERMINAL_SERVER)
		{
			StrCpy(tmp, sizeof(tmp), name);
			Format(name, size, "Local\\%s", tmp);
		}
	}
}