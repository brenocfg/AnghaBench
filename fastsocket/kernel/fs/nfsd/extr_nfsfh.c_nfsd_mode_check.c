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
typedef  int umode_t ;
struct svc_rqst {int rq_vers; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFMT ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_isdir ; 
 int /*<<< orphan*/  nfserr_notdir ; 
 int /*<<< orphan*/  nfserr_symlink ; 

__attribute__((used)) static inline __be32
nfsd_mode_check(struct svc_rqst *rqstp, umode_t mode, int type)
{
	/* Type can be negative when creating hardlinks - not to a dir */
	if (type > 0 && (mode & S_IFMT) != type) {
		if (rqstp->rq_vers == 4 && (mode & S_IFMT) == S_IFLNK)
			return nfserr_symlink;
		else if (type == S_IFDIR)
			return nfserr_notdir;
		else if ((mode & S_IFMT) == S_IFDIR)
			return nfserr_isdir;
		else
			return nfserr_inval;
	}
	if (type < 0 && (mode & S_IFMT) == -type) {
		if (rqstp->rq_vers == 4 && (mode & S_IFMT) == S_IFLNK)
			return nfserr_symlink;
		else if (type == -S_IFDIR)
			return nfserr_isdir;
		else
			return nfserr_notdir;
	}
	return 0;
}