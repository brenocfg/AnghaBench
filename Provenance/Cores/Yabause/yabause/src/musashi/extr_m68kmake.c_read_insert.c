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
 int /*<<< orphan*/  ID_INPUT_SEPARATOR ; 
 int MAX_INSERT_LENGTH ; 
 char* MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  error_exit (char*) ; 
 int fgetline (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_input_file ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void read_insert(char* insert)
{
	char* ptr = insert;
	char* overflow = insert + MAX_INSERT_LENGTH - MAX_LINE_LENGTH;
	int length;
	char* first_blank = NULL;

	first_blank = NULL;

	/* Skip any leading blank lines */
	for(length = 0;length == 0;length = fgetline(ptr, MAX_LINE_LENGTH, g_input_file))
		if(ptr >= overflow)
			error_exit("Buffer overflow reading inserts");
	if(length < 0)
		error_exit("Premature EOF while reading inserts");

	/* Advance and append newline */
	ptr += length;
	strcpy(ptr++, "\n");

	/* Read until next separator */
	for(;;)
	{
		/* Read a new line */
		if(ptr >= overflow)
			error_exit("Buffer overflow reading inserts");
		if((length = fgetline(ptr, MAX_LINE_LENGTH, g_input_file)) < 0)
			error_exit("Premature EOF while reading inserts");

		/* Stop if we read a separator */
		if(strcmp(ptr, ID_INPUT_SEPARATOR) == 0)
			break;

		/* keep track in case there are trailing blanks */
		if(length == 0)
		{
			if(first_blank == NULL)
				first_blank = ptr;
		}
		else
			first_blank = NULL;

		/* Advance and append newline */
		ptr += length;
		strcpy(ptr++, "\n");
	}

	/* kill any trailing blank lines */
	if(first_blank)
		ptr = first_blank;
	*ptr++ = 0;
}