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
struct seq_file {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (char*) ; 
 char* dentry_path (struct dentry*,char*,size_t) ; 
 char* mangle_path (char*,char*,char*) ; 
 int /*<<< orphan*/  seq_commit (struct seq_file*,int) ; 
 size_t seq_get_buf (struct seq_file*,char**) ; 

int seq_dentry(struct seq_file *m, struct dentry *dentry, char *esc)
{
	char *buf;
	size_t size = seq_get_buf(m, &buf);
	int res = -1;

	if (size) {
		char *p = dentry_path(dentry, buf, size);
		if (!IS_ERR(p)) {
			char *end = mangle_path(buf, p, esc);
			if (end)
				res = end - buf;
		}
	}
	seq_commit(m, res);

	return res;
}