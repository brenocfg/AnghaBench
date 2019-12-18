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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ (* toupper_t ) (int /*<<< orphan*/ ) ;
struct qstr {int len; int /*<<< orphan*/ * name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ affs_check_name (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
__affs_compare_dentry(struct dentry *dentry, struct qstr *a, struct qstr *b, toupper_t toupper)
{
	const u8 *aname = a->name;
	const u8 *bname = b->name;
	int len;

	/* 'a' is the qstr of an already existing dentry, so the name
	 * must be valid. 'b' must be validated first.
	 */

	if (affs_check_name(b->name,b->len))
		return 1;

	/* If the names are longer than the allowed 30 chars,
	 * the excess is ignored, so their length may differ.
	 */
	len = a->len;
	if (len >= 30) {
		if (b->len < 30)
			return 1;
		len = 30;
	} else if (len != b->len)
		return 1;

	for (; len > 0; len--)
		if (toupper(*aname++) != toupper(*bname++))
			return 1;

	return 0;
}