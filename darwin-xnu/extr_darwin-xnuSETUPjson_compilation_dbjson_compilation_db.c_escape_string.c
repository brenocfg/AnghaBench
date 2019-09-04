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
 char* malloc (size_t) ; 
 size_t strlen (char const*) ; 

char *
escape_string(const char *input)
{
	size_t len = strlen(input);
	size_t i, j;
	char *output = malloc(len * 4 + 1);

	for (i=0, j=0; i < len; i++) {
		char ch = input[i];

		if (ch == '\\' || ch == '"') {
			output[j++] = '\\';
			output[j++] = '\\'; /* output \\ in JSON, which the final shell will see as \ */
			output[j++] = '\\'; /* escape \ or ", which the final shell will see and pass to the compiler */
		}
		output[j++] = ch;
	}

	output[j] = '\0';

	return output;
}