#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rm_so; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  regmatch_len (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*) ; 

char   *regmatch_cpy (regmatch_t * m, char *dest, const char *src)
{
	if (m == NULL || m->rm_so < 0) {
		if (dest)
			dest[0] = '\0';
		return dest;
	}

	snprintf (dest, regmatch_len(m), "%s", src + m->rm_so);
    return dest;
}