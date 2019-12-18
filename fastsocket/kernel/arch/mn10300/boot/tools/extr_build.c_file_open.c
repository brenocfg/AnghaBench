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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ fd ; 
 scalar_t__ open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void file_open(const char *name)
{
	fd = open(name, O_RDONLY, 0);
	if (fd < 0)
		die("Unable to open `%s': %m", name);
}