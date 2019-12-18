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
 int /*<<< orphan*/  GETLINE_FILE_CORRUPT ; 
 int /*<<< orphan*/  GETLINE_OUT_OF_MEM ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 char* fgetln (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  get_line_error ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

char *
get_line(FILE *f)
{
	char *name, *temp;
	size_t len;

	name = fgetln(f, &len);
	if (!name) {
		get_line_error = ferror(f) ? GETLINE_FILE_CORRUPT : 0;
		return(0);
	}
	if (name[len-1] != '\n')
		len++;
	temp = malloc(len);
	if (!temp) {
		get_line_error = GETLINE_OUT_OF_MEM;
		return(0);
	}
	memcpy(temp, name, len-1);
	temp[len-1] = 0;
	return(temp);
}