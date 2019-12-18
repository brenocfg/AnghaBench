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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char *
bmake_strndup(const char *str, size_t max_len)
{
	size_t len;
	char *p;

	if (str == NULL)
		return NULL;

	len = strlen(str);
	if (len > max_len)
		len = max_len;
	p = bmake_malloc(len + 1);
	memcpy(p, str, len);
	p[len] = '\0';

	return(p);
}