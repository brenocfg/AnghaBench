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
struct autofs_sb_info {int dummy; } ;
struct autofs_info {int dummy; } ;

/* Variables and functions */
 int S_IFDIR ; 
 struct autofs_info* autofs4_init_ino (int /*<<< orphan*/ *,struct autofs_sb_info*,int) ; 

__attribute__((used)) static struct autofs_info *autofs4_mkroot(struct autofs_sb_info *sbi)
{
	struct autofs_info *ino;

	ino = autofs4_init_ino(NULL, sbi, S_IFDIR | 0755);
	if (!ino)
		return NULL;

	return ino;
}