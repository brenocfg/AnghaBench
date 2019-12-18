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
typedef  int /*<<< orphan*/  pcname ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  READ_UINT (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

UINT GetMachineRand()
{
	char pcname[MAX_SIZE];
	UCHAR hash[SHA1_SIZE];

	Zero(pcname, sizeof(pcname));
	GetMachineName(pcname, sizeof(pcname));

	Sha1(hash, pcname, StrLen(pcname));

	return READ_UINT(hash);
}