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
 int /*<<< orphan*/ * make_tube (char const*) ; 
 int ms_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tube_dref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tubes ; 

__attribute__((used)) static Tube *
make_and_insert_tube(const char *name)
{
    int r;
    Tube *t = NULL;

    t = make_tube(name);
    if (!t)
        return NULL;

    /* We want this global tube list to behave like "weak" refs, so don't
     * increment the ref count. */
    r = ms_append(&tubes, t);
    if (!r)
        return tube_dref(t), (Tube *) 0;

    return t;
}