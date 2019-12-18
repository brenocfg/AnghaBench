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
 char* bmake_malloc (size_t) ; 
 char* bmake_strdup (char const*) ; 
 int /*<<< orphan*/  isalpha (unsigned char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
explode(const char *flags)
{
    size_t len;
    char *nf, *st;
    const char *f;

    if (flags == NULL)
	return NULL;

    for (f = flags; *f; f++)
	if (!isalpha((unsigned char)*f))
	    break;

    if (*f)
	return bmake_strdup(flags);

    len = strlen(flags);
    st = nf = bmake_malloc(len * 3 + 1);
    while (*flags) {
	*nf++ = '-';
	*nf++ = *flags++;
	*nf++ = ' ';
    }
    *nf = '\0';
    return st;
}