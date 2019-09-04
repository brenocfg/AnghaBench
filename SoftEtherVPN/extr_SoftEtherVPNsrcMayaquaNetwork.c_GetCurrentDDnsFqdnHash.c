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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ClearStr (char*,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetCurrentDDnsFqdn (char*,int) ; 
 int MAX_SIZE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

UINT GetCurrentDDnsFqdnHash()
{
	UINT ret;
	UCHAR hash[SHA1_SIZE];
	char name[MAX_SIZE];

	ClearStr(name, sizeof(name));
	GetCurrentDDnsFqdn(name, sizeof(name));

	Trim(name);
	StrUpper(name);

	Sha1(hash, name, StrLen(name));

	Copy(&ret, hash, sizeof(UINT));

	return ret;
}