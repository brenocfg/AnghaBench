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
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_First (int /*<<< orphan*/ ) ; 
 int Lst_ForEachFrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int (*) (void*,void*),void*) ; 

int
Lst_ForEach(Lst l, int (*proc)(void *, void *), void *d)
{
    return Lst_ForEachFrom(l, Lst_First(l), proc, d);
}