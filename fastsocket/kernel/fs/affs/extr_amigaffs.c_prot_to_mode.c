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
typedef  int mode_t ;

/* Variables and functions */
 int FIBF_GRP_EXECUTE ; 
 int FIBF_GRP_READ ; 
 int FIBF_GRP_WRITE ; 
 int FIBF_NOEXECUTE ; 
 int FIBF_NOREAD ; 
 int FIBF_NOWRITE ; 
 int FIBF_OTR_EXECUTE ; 
 int FIBF_OTR_READ ; 
 int FIBF_OTR_WRITE ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 

mode_t
prot_to_mode(u32 prot)
{
	int mode = 0;

	if (!(prot & FIBF_NOWRITE))
		mode |= S_IWUSR;
	if (!(prot & FIBF_NOREAD))
		mode |= S_IRUSR;
	if (!(prot & FIBF_NOEXECUTE))
		mode |= S_IXUSR;
	if (prot & FIBF_GRP_WRITE)
		mode |= S_IWGRP;
	if (prot & FIBF_GRP_READ)
		mode |= S_IRGRP;
	if (prot & FIBF_GRP_EXECUTE)
		mode |= S_IXGRP;
	if (prot & FIBF_OTR_WRITE)
		mode |= S_IWOTH;
	if (prot & FIBF_OTR_READ)
		mode |= S_IROTH;
	if (prot & FIBF_OTR_EXECUTE)
		mode |= S_IXOTH;

	return mode;
}