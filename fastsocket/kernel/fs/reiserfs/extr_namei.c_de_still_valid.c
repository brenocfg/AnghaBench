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
struct reiserfs_dir_entry {int de_namelen; int /*<<< orphan*/  de_name; } ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_de_name_and_namelen (struct reiserfs_dir_entry*) ; 

__attribute__((used)) static int de_still_valid(const char *name, int len,
			  struct reiserfs_dir_entry *de)
{
	struct reiserfs_dir_entry tmp = *de;

	// recalculate pointer to name and name length
	set_de_name_and_namelen(&tmp);
	// FIXME: could check more
	if (tmp.de_namelen != len || memcmp(name, de->de_name, len))
		return 0;
	return 1;
}