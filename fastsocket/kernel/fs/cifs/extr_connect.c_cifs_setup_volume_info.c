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
struct smb_vol {int /*<<< orphan*/ * iocharset; int /*<<< orphan*/ * local_nls; int /*<<< orphan*/ * username; scalar_t__ nullauth; } ;

/* Variables and functions */
 int EINVAL ; 
 int ELIBACC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cERROR (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cFYI (int,char*,...) ; 
 scalar_t__ cifs_parse_mount_options (char*,char const*,struct smb_vol*) ; 
 int /*<<< orphan*/  cifserror (char*) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * load_nls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * load_nls_default () ; 

__attribute__((used)) static int
cifs_setup_volume_info(struct smb_vol *volume_info, char *mount_data,
			const char *devname)
{
	int rc = 0;

	if (cifs_parse_mount_options(mount_data, devname, volume_info))
		return -EINVAL;

	if (volume_info->nullauth) {
		cFYI(1, "null user");
		volume_info->username = kzalloc(1, GFP_KERNEL);
		if (volume_info->username == NULL)
			return -ENOMEM;
	} else if (volume_info->username) {
		/* BB fixme parse for domain name here */
		cFYI(1, "Username: %s", volume_info->username);
	} else {
		cifserror("No username specified");
	/* In userspace mount helper we can get user name from alternate
	   locations such as env variables and files on disk */
		return -EINVAL;
	}

	/* this is needed for ASCII cp to Unicode converts */
	if (volume_info->iocharset == NULL) {
		/* load_nls_default cannot return null */
		volume_info->local_nls = load_nls_default();
	} else {
		volume_info->local_nls = load_nls(volume_info->iocharset);
		if (volume_info->local_nls == NULL) {
			cERROR(1, "CIFS mount error: iocharset %s not found",
				 volume_info->iocharset);
			return -ELIBACC;
		}
	}

	return rc;
}