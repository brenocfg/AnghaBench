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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 scalar_t__ StrLen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void remove_comments(char *string, char *start_token, char *end_token) {
	int in_string = 0, escaped = 0;
	UINT i;
	char *ptr = NULL, current_char;
	UINT start_token_len = StrLen(start_token);
	UINT end_token_len = StrLen(end_token);
	if (start_token_len == 0 || end_token_len == 0) {
		return;
	}
	while ((current_char = *string) != '\0') {
		if (current_char == '\\' && !escaped) {
			escaped = 1;
			string++;
			continue;
		}
		else if (current_char == '\"' && !escaped) {
			in_string = !in_string;
		}
		else if (!in_string && strncmp(string, start_token, start_token_len) == 0) {
			for (i = 0; i < start_token_len; i++) {
				string[i] = ' ';
			}
			string = string + start_token_len;
			ptr = strstr(string, end_token);
			if (!ptr) {
				return;
			}
			for (i = 0; i < (ptr - string) + end_token_len; i++) {
				string[i] = ' ';
			}
			string = ptr + end_token_len - 1;
		}
		escaped = 0;
		string++;
	}
}