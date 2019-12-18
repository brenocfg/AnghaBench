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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_command (char*) ; 
 int /*<<< orphan*/  shell_prompt ; 

void 
shell_op()
{
	char *string;

	if (((string = get_string(shell_prompt, TRUE)) != NULL) && 
			(*string != '\0'))
	{
		sh_command(string);
		free(string);
	}
}