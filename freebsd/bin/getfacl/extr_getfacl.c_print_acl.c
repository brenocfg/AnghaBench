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
struct stat {int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
typedef  scalar_t__ acl_type_t ;
typedef  char* acl_t ;

/* Variables and functions */
 int ACL_TEXT_APPEND_ID ; 
 int ACL_TEXT_NUMERIC_IDS ; 
 int ACL_TEXT_VERBOSE ; 
 scalar_t__ ACL_TYPE_DEFAULT ; 
 scalar_t__ ACL_TYPE_NFS4 ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  _PC_ACL_NFS4 ; 
 int /*<<< orphan*/  acl_free (char*) ; 
 char* acl_from_stat (struct stat*) ; 
 char* acl_get_file (char*,scalar_t__) ; 
 char* acl_get_link_np (char*,scalar_t__) ; 
 char* acl_to_text_np (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ errno ; 
 char* getgname (int /*<<< orphan*/ ) ; 
 char* getuname (int /*<<< orphan*/ ) ; 
 int lpathconf (char*,int /*<<< orphan*/ ) ; 
 int lstat (char*,struct stat*) ; 
 scalar_t__ more_than_one ; 
 int pathconf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int
print_acl(char *path, acl_type_t type, int hflag, int iflag, int nflag,
    int qflag, int vflag)
{
	struct stat	sb;
	acl_t	acl;
	char	*acl_text;
	int	error, flags = 0, ret;

	if (hflag)
		error = lstat(path, &sb);
	else
		error = stat(path, &sb);
	if (error == -1) {
		warn("%s: stat() failed", path);
		return(-1);
	}

	if (hflag)
		ret = lpathconf(path, _PC_ACL_NFS4);
	else
		ret = pathconf(path, _PC_ACL_NFS4);
	if (ret > 0) {
		if (type == ACL_TYPE_DEFAULT) {
			warnx("%s: there are no default entries in NFSv4 ACLs",
			    path);
			return (-1);
		}
		type = ACL_TYPE_NFS4;
	} else if (ret < 0 && errno != EINVAL) {
		warn("%s: pathconf(..., _PC_ACL_NFS4) failed", path);
		return (-1);
	}

	if (more_than_one)
		printf("\n");
	else
		more_than_one++;

	if (!qflag)
		printf("# file: %s\n# owner: %s\n# group: %s\n", path,
		    getuname(sb.st_uid), getgname(sb.st_gid));

	if (hflag)
		acl = acl_get_link_np(path, type);
	else
		acl = acl_get_file(path, type);
	if (!acl) {
		if (errno != EOPNOTSUPP) {
			warn("%s", path);
			return(-1);
		}
		errno = 0;
		if (type == ACL_TYPE_DEFAULT)
			return(0);
		acl = acl_from_stat(&sb);
		if (!acl) {
			warn("%s: acl_from_stat() failed", path);
			return(-1);
		}
	}

	if (iflag)
		flags |= ACL_TEXT_APPEND_ID;

	if (nflag)
		flags |= ACL_TEXT_NUMERIC_IDS;

	if (vflag)
		flags |= ACL_TEXT_VERBOSE;

	acl_text = acl_to_text_np(acl, 0, flags);
	if (!acl_text) {
		warn("%s: acl_to_text_np() failed", path);
		return(-1);
	}

	printf("%s", acl_text);

	(void)acl_free(acl);
	(void)acl_free(acl_text);

	return(0);
}