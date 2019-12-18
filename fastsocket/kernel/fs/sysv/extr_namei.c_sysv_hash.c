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
struct qstr {scalar_t__ len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ SYSV_NAMELEN ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sysv_hash(struct dentry *dentry, struct qstr *qstr)
{
	/* Truncate the name in place, avoids having to define a compare
	   function. */
	if (qstr->len > SYSV_NAMELEN) {
		qstr->len = SYSV_NAMELEN;
		qstr->hash = full_name_hash(qstr->name, qstr->len);
	}
	return 0;
}