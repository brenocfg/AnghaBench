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

/* Variables and functions */
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  cmdloop (int /*<<< orphan*/ ) ; 
 char* expandstr (char const*) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  popfile () ; 
 int /*<<< orphan*/  setinputfd (int,int) ; 

__attribute__((used)) static void
read_profile(const char *name)
{
	int fd;
	const char *expandedname;

	expandedname = expandstr(name);
	if (expandedname == NULL)
		return;
	INTOFF;
	if ((fd = open(expandedname, O_RDONLY | O_CLOEXEC)) >= 0)
		setinputfd(fd, 1);
	INTON;
	if (fd < 0)
		return;
	cmdloop(0);
	popfile();
}