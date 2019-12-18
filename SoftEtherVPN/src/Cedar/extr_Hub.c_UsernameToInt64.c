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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_LIST_EXCLUDED_PREFIX ; 
 int /*<<< orphan*/  ACCESS_LIST_INCLUDED_PREFIX ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  MAX_USERNAME_LEN ; 
 int /*<<< orphan*/  MakeSimpleUsernameRemoveNtDomain (char*,int,char*) ; 
 int /*<<< orphan*/  Rand64 () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ StartWith (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

UINT64 UsernameToInt64(char *name)
{
	UCHAR hash[SHA1_SIZE];
	UINT64 ret;
	char tmp[MAX_USERNAME_LEN + 1];
	// Validate arguments
	if (name == 0 || IsEmptyStr(name))
	{
		return 0;
	}

	if (StartWith(name, ACCESS_LIST_INCLUDED_PREFIX) || StartWith(name, ACCESS_LIST_EXCLUDED_PREFIX))
	{
		return Rand64();
	}

	MakeSimpleUsernameRemoveNtDomain(tmp, sizeof(tmp), name);
	Trim(tmp);
	StrUpper(tmp);

	if (StrLen(tmp) == 0)
	{
		return 0;
	}

	Sha0(hash, tmp, StrLen(tmp));
	Copy(&ret, hash, sizeof(ret));

	return ret;
}