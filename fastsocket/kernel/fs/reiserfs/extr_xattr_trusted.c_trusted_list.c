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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static size_t trusted_list(struct inode *inode, char *list, size_t list_size,
			   const char *name, size_t name_len)
{
	const size_t len = name_len + 1;

	if (!capable(CAP_SYS_ADMIN) || IS_PRIVATE(inode))
		return 0;

	if (list && len <= list_size) {
		memcpy(list, name, name_len);
		list[name_len] = '\0';
	}
	return len;
}