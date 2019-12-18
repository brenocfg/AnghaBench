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
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strdup (char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *
br_strndup (const char *str, size_t size)
{
	char *result = (char *) NULL;
	size_t len;

	if (str == (const char *) NULL)
		return (char *) NULL;

	len = strlen (str);
	if (len == 0)
		return strdup ("");
	if (size > len)
		size = len;

	result = (char *) malloc (len + 1);
	memcpy (result, str, size);
	result[size] = '\0';
	return result;
}