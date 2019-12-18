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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int SmbAuthenticate (char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool SmbPerformMsChapV2Auth(char* name, char* domainname, char* groupname, UCHAR* challenge8, UCHAR* MsChapV2_ClientResponse, UCHAR* nt_pw_hash_hash, UINT timeout)
{
	return SmbAuthenticate(name, "", domainname, groupname, timeout, challenge8, MsChapV2_ClientResponse, nt_pw_hash_hash);
}