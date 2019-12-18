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
typedef  int /*<<< orphan*/  Tube ;

/* Variables and functions */
 int /*<<< orphan*/ * make_and_insert_tube (char const*) ; 
 int /*<<< orphan*/ * tube_find (char const*) ; 

Tube *
tube_find_or_make(const char *name)
{
    Tube *t = tube_find(name);
    if (t)
        return t;
    return make_and_insert_tube(name);
}