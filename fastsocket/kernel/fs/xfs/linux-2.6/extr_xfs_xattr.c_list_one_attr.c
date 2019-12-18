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
typedef  size_t ssize_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static int
list_one_attr(const char *name, const size_t len, void *data,
		size_t size, ssize_t *result)
{
	char *p = data + *result;

	*result += len;
	if (!size)
		return 0;
	if (*result > size)
		return -ERANGE;

	strcpy(p, name);
	return 0;
}