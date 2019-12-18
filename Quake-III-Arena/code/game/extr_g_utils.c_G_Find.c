#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  inuse; } ;
typedef  TYPE_1__ gentity_t ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_7__ {size_t num_entities; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_stricmp (char*,char const*) ; 
 TYPE_1__* g_entities ; 
 TYPE_2__ level ; 

gentity_t *G_Find (gentity_t *from, int fieldofs, const char *match)
{
	char	*s;

	if (!from)
		from = g_entities;
	else
		from++;

	for ( ; from < &g_entities[level.num_entities] ; from++)
	{
		if (!from->inuse)
			continue;
		s = *(char **) ((byte *)from + fieldofs);
		if (!s)
			continue;
		if (!Q_stricmp (s, match))
			return from;
	}

	return NULL;
}