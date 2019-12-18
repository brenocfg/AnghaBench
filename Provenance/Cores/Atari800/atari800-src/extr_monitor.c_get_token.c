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
 char* token_ptr ; 

__attribute__((used)) static char *get_token(void)
{
	char *p = token_ptr;
	while (*p == ' ')
		p++;
	if (*p == '\0')
		return NULL;
	token_ptr = p;
	do {
		token_ptr++;
		if (*token_ptr == ' ') {
			*token_ptr++ = '\0';
			break;
		}
	} while (*token_ptr != '\0');
	return p;
}