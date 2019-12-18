#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buf; } ;
struct demangle_data {char* p; int array; TYPE_1__ array_str; } ;

/* Variables and functions */
 scalar_t__ ELFTC_ISDIGIT (char const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dest_cstring (TYPE_1__*) ; 
 int init_cstring (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static bool
read_array(struct demangle_data *d)
{
	size_t len;
	const char *end;

	if (d == NULL || d->p == NULL)
		return (false);

	end = d->p;
	assert(end != NULL);

	for (;;) {
		if (*end == '\0')
			return (false);

		if (ELFTC_ISDIGIT(*end) == 0)
			break;

		++end;
	}

	if (*end != '_')
		return (false);

	len = end - d->p;
	assert(len > 0);

	dest_cstring(&d->array_str);
	if (init_cstring(&d->array_str, len + 3) == false)
		return (false);

	strncpy(d->array_str.buf + 1, d->p, len);
	*d->array_str.buf = '[';
	*(d->array_str.buf + len + 1) = ']';

	d->array = true;
	d->p = end + 1;

	return (true);
}