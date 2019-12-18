#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* key; char* value; struct TYPE_4__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_5__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void PrintEntity (entity_t *ent)
{
	epair_t	*ep;
	
	printf ("------- entity %p -------\n", ent);
	for (ep=ent->epairs ; ep ; ep=ep->next)
	{
		printf ("%s = %s\n", ep->key, ep->value);
	}

}