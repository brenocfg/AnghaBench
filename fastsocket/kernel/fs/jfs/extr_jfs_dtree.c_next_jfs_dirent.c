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
struct jfs_dirent {int name_len; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */

__attribute__((used)) static inline struct jfs_dirent *next_jfs_dirent(struct jfs_dirent *dirent)
{
	return (struct jfs_dirent *)
		((char *)dirent +
		 ((sizeof (struct jfs_dirent) + dirent->name_len + 1 +
		   sizeof (loff_t) - 1) &
		  ~(sizeof (loff_t) - 1)));
}