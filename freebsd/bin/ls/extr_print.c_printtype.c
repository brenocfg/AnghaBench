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
typedef  int u_int ;

/* Variables and functions */
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFSOCK 129 
#define  S_IFWHT 128 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 scalar_t__ f_slash ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static int
printtype(u_int mode)
{

	if (f_slash) {
		if ((mode & S_IFMT) == S_IFDIR) {
			(void)putchar('/');
			return (1);
		}
		return (0);
	}

	switch (mode & S_IFMT) {
	case S_IFDIR:
		(void)putchar('/');
		return (1);
	case S_IFIFO:
		(void)putchar('|');
		return (1);
	case S_IFLNK:
		(void)putchar('@');
		return (1);
	case S_IFSOCK:
		(void)putchar('=');
		return (1);
	case S_IFWHT:
		(void)putchar('%');
		return (1);
	default:
		break;
	}
	if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
		(void)putchar('*');
		return (1);
	}
	return (0);
}