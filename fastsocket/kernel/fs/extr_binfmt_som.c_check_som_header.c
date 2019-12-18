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
struct som_hdr {scalar_t__ system_id; scalar_t__ a_magic; scalar_t__ version_id; } ;

/* Variables and functions */
 int ENOEXEC ; 
 scalar_t__ SOM_EXEC_DEMAND ; 
 scalar_t__ SOM_EXEC_NONSHARE ; 
 scalar_t__ SOM_EXEC_SHARE ; 
 scalar_t__ SOM_ID_NEW ; 
 scalar_t__ SOM_ID_OLD ; 
 scalar_t__ SOM_SID_PARISC_1_0 ; 
 scalar_t__ SOM_SID_PARISC_1_1 ; 
 scalar_t__ SOM_SID_PARISC_2_0 ; 

__attribute__((used)) static int check_som_header(struct som_hdr *som_ex)
{
	int *buf = (int *)som_ex;
	int i, ck;

	if (som_ex->system_id != SOM_SID_PARISC_1_0 &&
	    som_ex->system_id != SOM_SID_PARISC_1_1 &&
	    som_ex->system_id != SOM_SID_PARISC_2_0)
		return -ENOEXEC;

	if (som_ex->a_magic != SOM_EXEC_NONSHARE &&
	    som_ex->a_magic != SOM_EXEC_SHARE &&
	    som_ex->a_magic != SOM_EXEC_DEMAND)
		return -ENOEXEC;

	if (som_ex->version_id != SOM_ID_OLD &&
	    som_ex->version_id != SOM_ID_NEW)
		return -ENOEXEC;

	ck = 0;
	for (i=0; i<32; i++)
		ck ^= buf[i];
	if (ck != 0)
		return -ENOEXEC;

	return 0;
}