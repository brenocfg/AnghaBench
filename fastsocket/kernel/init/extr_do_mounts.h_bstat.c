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
typedef  int /*<<< orphan*/  u32 ;
struct stat {int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ sys_newstat (char*,struct stat*) ; 

__attribute__((used)) static inline u32 bstat(char *name)
{
	struct stat stat;
	if (sys_newstat(name, &stat) != 0)
		return 0;
	if (!S_ISBLK(stat.st_mode))
		return 0;
	return stat.st_rdev;
}