#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qstr {char const* name; int len; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_op; } ;
struct TYPE_3__ {int (* d_compare ) (struct dentry*,TYPE_2__*,struct qstr*) ;} ;

/* Variables and functions */
 int stub1 (struct dentry*,TYPE_2__*,struct qstr*) ; 

__attribute__((used)) static int
isofs_cmp(struct dentry *dentry, const char *compare, int dlen)
{
	struct qstr qstr;

	if (!compare)
		return 1;

	/* check special "." and ".." files */
	if (dlen == 1) {
		/* "." */
		if (compare[0] == 0) {
			if (!dentry->d_name.len)
				return 0;
			compare = ".";
		} else if (compare[0] == 1) {
			compare = "..";
			dlen = 2;
		}
	}

	qstr.name = compare;
	qstr.len = dlen;
	return dentry->d_op->d_compare(dentry, &dentry->d_name, &qstr);
}