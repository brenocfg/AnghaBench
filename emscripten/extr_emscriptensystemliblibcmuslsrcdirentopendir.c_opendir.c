#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SYS_close ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* calloc (int,int) ; 
 int open (char const*,int) ; 

DIR *opendir(const char *name)
{
	int fd;
	DIR *dir;

	if ((fd = open(name, O_RDONLY|O_DIRECTORY|O_CLOEXEC)) < 0)
		return 0;
	if (!(dir = calloc(1, sizeof *dir))) {
		__syscall(SYS_close, fd);
		return 0;
	}
	dir->fd = fd;
	return dir;
}