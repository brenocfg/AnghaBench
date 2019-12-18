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
struct fb_data_t {char* name; char* value; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static int proc_read_foobar(char *page, char **start,
			    off_t off, int count, 
			    int *eof, void *data)
{
	int len;
	struct fb_data_t *fb_data = (struct fb_data_t *)data;

	/* DON'T DO THAT - buffer overruns are bad */
	len = sprintf(page, "%s = '%s'\n", 
		      fb_data->name, fb_data->value);

	return len;
}