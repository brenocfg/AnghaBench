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
struct path {int dummy; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 int PTR_ERR (char*) ; 
 char* __d_path (struct path*,struct path*,char*,size_t) ; 
 int /*<<< orphan*/  dcache_lock ; 
 char* mangle_path (char*,char*,char*) ; 
 int /*<<< orphan*/  seq_commit (struct seq_file*,int) ; 
 size_t seq_get_buf (struct seq_file*,char**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int seq_path_root(struct seq_file *m, struct path *path, struct path *root,
		  char *esc)
{
	char *buf;
	size_t size = seq_get_buf(m, &buf);
	int res = -ENAMETOOLONG;

	if (size) {
		char *p;

		spin_lock(&dcache_lock);
		p = __d_path(path, root, buf, size);
		spin_unlock(&dcache_lock);
		res = PTR_ERR(p);
		if (!IS_ERR(p)) {
			char *end = mangle_path(buf, p, esc);
			if (end)
				res = end - buf;
			else
				res = -ENAMETOOLONG;
		}
	}
	seq_commit(m, res);

	return res < 0 ? res : 0;
}