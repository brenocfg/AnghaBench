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
struct section {int entsize; int sz; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_ent_count(struct section *s, int *ent_count)
{
	if (s->entsize == 0) {
		warnx("section %s has entry size 0", s->name);
		return (0);
	} else if (s->sz / s->entsize > INT_MAX) {
		warnx("section %s has invalid section count", s->name);
		return (0);
	}
	*ent_count = (int)(s->sz / s->entsize);
	return (1);
}