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
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ isspace (int) ; 

__attribute__((used)) static unsigned int get_number(FILE *fp)
{
    int c, val;

    /* Skip leading whitespace */
    do {
	c = fgetc(fp);
	if (c == EOF)
	    die("%s: end of file\n", filename);
	if (c == '#') {
	    /* Ignore comments 'till end of line */
	    do {
		c = fgetc(fp);
		if (c == EOF)
		    die("%s: end of file\n", filename);
	    } while (c != '\n');
	}
    } while (isspace(c));

    /* Parse decimal number */
    val = 0;
    while (isdigit(c)) {
	val = 10*val+c-'0';
	c = fgetc(fp);
	if (c == EOF)
	    die("%s: end of file\n", filename);
    }
    return val;
}