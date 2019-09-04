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
struct statvfs {int dummy; } ;
struct statfs {int dummy; } ;

/* Variables and functions */
 scalar_t__ __statfs (char const*,struct statfs*) ; 
 int /*<<< orphan*/  fixup (struct statvfs*,struct statfs*) ; 

int statvfs(const char *restrict path, struct statvfs *restrict buf)
{
	struct statfs kbuf;
	if (__statfs(path, &kbuf)<0) return -1;
	fixup(buf, &kbuf);
	return 0;
}