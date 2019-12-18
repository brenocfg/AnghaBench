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
struct TYPE_3__ {scalar_t__ rm_so; int rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ flex_alloc (int) ; 
 int /*<<< orphan*/  flexfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

char   *regmatch_dup (regmatch_t * m, const char *src)
{
	char   *str;
	int     len;

	if (m == NULL || m->rm_so < 0)
		return NULL;
	len = m->rm_eo - m->rm_so;
	str = (char *) flex_alloc ((len + 1) * sizeof (char));
	if (!str)
		flexfatal(_("Unable to allocate a copy of the match"));
	strncpy (str, src + m->rm_so, len);
	str[len] = 0;
	return str;
}