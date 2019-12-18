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
struct nameidata {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 int ENOMEM ; 
 char* ERR_PTR (int) ; 
 scalar_t__ PATH_MAX ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 
 int /*<<< orphan*/  server_from_dentry (struct dentry*) ; 
 int smb_proc_read_link (int /*<<< orphan*/ ,struct dentry*,char*,scalar_t__) ; 

__attribute__((used)) static void *smb_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	char *link = __getname();
	DEBUG1("followlink of %s/%s\n", DENTRY_PATH(dentry));

	if (!link) {
		link = ERR_PTR(-ENOMEM);
	} else {
		int len = smb_proc_read_link(server_from_dentry(dentry),
						dentry, link, PATH_MAX - 1);
		if (len < 0) {
			__putname(link);
			link = ERR_PTR(len);
		} else {
			link[len] = 0;
		}
	}
	nd_set_link(nd, link);
	return NULL;
}