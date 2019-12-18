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
struct line {int dummy; } ;

/* Variables and functions */
 int line_setup (struct line*,unsigned int,char*,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int line_remove(struct line *lines, unsigned int num, int n, char **error_out)
{
	int err;
	char config[sizeof("conxxxx=none\0")];

	sprintf(config, "%d=none", n);
	err = line_setup(lines, num, config, error_out);
	if (err >= 0)
		err = 0;
	return err;
}