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
struct demangle_data {char* p; int class_name; int /*<<< orphan*/  vec; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 size_t strtol (char*,char**,int) ; 
 int vector_str_push (int /*<<< orphan*/ *,char*,size_t) ; 

__attribute__((used)) static bool
read_class(struct demangle_data *d)
{
	size_t len;
	char *str;

	if (d == NULL)
		return (false);

	len = strtol(d->p, &str, 10);
	if (len == 0 && (errno == EINVAL || errno == ERANGE))
		return (false);

	assert(len > 0);
	assert(str != NULL);

	if (vector_str_push(&d->vec, str, len) == false)
		return (false);

	d->p = str + len;

	d->class_name = true;

	return (true);
}