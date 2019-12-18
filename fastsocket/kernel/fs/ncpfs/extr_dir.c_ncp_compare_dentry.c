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
struct qstr {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCP_IO_TABLE (struct dentry*) ; 
 scalar_t__ ncp_case_sensitive (int /*<<< orphan*/ ) ; 
 int ncp_strnicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ncp_compare_dentry(struct dentry *dentry, struct qstr *a, struct qstr *b)
{
	if (a->len != b->len)
		return 1;

	if (ncp_case_sensitive(dentry->d_inode))
		return strncmp(a->name, b->name, a->len);

	return ncp_strnicmp(NCP_IO_TABLE(dentry), a->name, b->name, a->len);
}