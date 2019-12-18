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
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static size_t security_list(struct inode *inode, char *list, size_t list_len,
			    const char *name, size_t namelen)
{
	const size_t len = namelen + 1;

	if (IS_PRIVATE(inode))
		return 0;

	if (list && len <= list_len) {
		memcpy(list, name, namelen);
		list[namelen] = '\0';
	}

	return len;
}