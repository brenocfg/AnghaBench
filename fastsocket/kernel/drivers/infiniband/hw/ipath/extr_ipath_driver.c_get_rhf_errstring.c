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
typedef  int u32 ;

/* Variables and functions */
 int INFINIPATH_RHF_H_IBERR ; 
 int INFINIPATH_RHF_H_ICRCERR ; 
 int INFINIPATH_RHF_H_IHDRERR ; 
 int INFINIPATH_RHF_H_LENERR ; 
 int INFINIPATH_RHF_H_MKERR ; 
 int INFINIPATH_RHF_H_MTUERR ; 
 int INFINIPATH_RHF_H_PARITYERR ; 
 int INFINIPATH_RHF_H_TIDERR ; 
 int INFINIPATH_RHF_H_VCRCERR ; 
 int INFINIPATH_RHF_L_SWA ; 
 int INFINIPATH_RHF_L_SWB ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static void get_rhf_errstring(u32 err, char *msg, size_t len)
{
	/* if no errors, and so don't need to check what's first */
	*msg = '\0';

	if (err & INFINIPATH_RHF_H_ICRCERR)
		strlcat(msg, "icrcerr ", len);
	if (err & INFINIPATH_RHF_H_VCRCERR)
		strlcat(msg, "vcrcerr ", len);
	if (err & INFINIPATH_RHF_H_PARITYERR)
		strlcat(msg, "parityerr ", len);
	if (err & INFINIPATH_RHF_H_LENERR)
		strlcat(msg, "lenerr ", len);
	if (err & INFINIPATH_RHF_H_MTUERR)
		strlcat(msg, "mtuerr ", len);
	if (err & INFINIPATH_RHF_H_IHDRERR)
		/* infinipath hdr checksum error */
		strlcat(msg, "ipathhdrerr ", len);
	if (err & INFINIPATH_RHF_H_TIDERR)
		strlcat(msg, "tiderr ", len);
	if (err & INFINIPATH_RHF_H_MKERR)
		/* bad port, offset, etc. */
		strlcat(msg, "invalid ipathhdr ", len);
	if (err & INFINIPATH_RHF_H_IBERR)
		strlcat(msg, "iberr ", len);
	if (err & INFINIPATH_RHF_L_SWA)
		strlcat(msg, "swA ", len);
	if (err & INFINIPATH_RHF_L_SWB)
		strlcat(msg, "swB ", len);
}