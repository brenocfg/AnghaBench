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
struct pseminfo {int /*<<< orphan*/  psem_mode; int /*<<< orphan*/  psem_gid; int /*<<< orphan*/  psem_uid; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int posix_cred_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
psem_access(struct pseminfo *pinfo, int mode, kauth_cred_t cred)
{
	int mode_req = ((mode & FREAD) ? S_IRUSR : 0) |
		       ((mode & FWRITE) ? S_IWUSR : 0);

	/* Otherwise, user id 0 always gets access. */
	if (!suser(cred, NULL))
		return (0);

	return(posix_cred_access(cred, pinfo->psem_uid, pinfo->psem_gid, pinfo->psem_mode, mode_req));
}