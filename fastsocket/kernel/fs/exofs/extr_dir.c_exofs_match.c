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
struct exofs_dir_entry {int name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  inode_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int exofs_match(int len, const unsigned char *name,
					struct exofs_dir_entry *de)
{
	if (len != de->name_len)
		return 0;
	if (!de->inode_no)
		return 0;
	return !memcmp(name, de->name, len);
}