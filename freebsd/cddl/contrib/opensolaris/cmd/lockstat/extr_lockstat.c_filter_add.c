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
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,void*,char*,void*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
filter_add(char **filt, char *what, uintptr_t base, uintptr_t size)
{
	char buf[256], *c = buf, *new;
	int len, newlen;

	if (*filt == NULL) {
		*filt = malloc(1);
		*filt[0] = '\0';
	}

#ifdef illumos
	(void) sprintf(c, "%s(%s >= 0x%p && %s < 0x%p)", *filt[0] != '\0' ?
	    " || " : "", what, (void *)base, what, (void *)(base + size));
#else
	(void) sprintf(c, "%s(%s >= %p && %s < %p)", *filt[0] != '\0' ?
	    " || " : "", what, (void *)base, what, (void *)(base + size));
#endif

	newlen = (len = strlen(*filt) + 1) + strlen(c);
	new = malloc(newlen);
	bcopy(*filt, new, len);
	(void) strcat(new, c);
	free(*filt);
	*filt = new;
}