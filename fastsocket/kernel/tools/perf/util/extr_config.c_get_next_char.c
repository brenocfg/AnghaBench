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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/ * config_file ; 
 int config_file_eof ; 
 int /*<<< orphan*/  config_linenr ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_next_char(void)
{
	int c;
	FILE *f;

	c = '\n';
	if ((f = config_file) != NULL) {
		c = fgetc(f);
		if (c == '\r') {
			/* DOS like systems */
			c = fgetc(f);
			if (c != '\n') {
				ungetc(c, f);
				c = '\r';
			}
		}
		if (c == '\n')
			config_linenr++;
		if (c == EOF) {
			config_file_eof = 1;
			c = '\n';
		}
	}
	return c;
}