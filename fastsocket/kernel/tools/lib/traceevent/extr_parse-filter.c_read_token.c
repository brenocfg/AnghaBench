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
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int EVENT_NEWLINE ; 
 int EVENT_SPACE ; 
 int /*<<< orphan*/  free_token (char*) ; 
 char* malloc_or_die (int) ; 
 char pevent_peek_char () ; 
 int pevent_read_token (char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static enum event_type read_token(char **tok)
{
	enum event_type type;
	char *token = NULL;

	do {
		free_token(token);
		type = pevent_read_token(&token);
	} while (type == EVENT_NEWLINE || type == EVENT_SPACE);

	/* If token is = or ! check to see if the next char is ~ */
	if (token &&
	    (strcmp(token, "=") == 0 || strcmp(token, "!") == 0) &&
	    pevent_peek_char() == '~') {
		/* append it */
		*tok = malloc_or_die(3);
		sprintf(*tok, "%c%c", *token, '~');
		free_token(token);
		/* Now remove the '~' from the buffer */
		pevent_read_token(&token);
		free_token(token);
	} else
		*tok = token;

	return type;
}