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
struct TYPE_3__ {int id; char const* name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* names ; 
 char const* unknowndioname ; 

__attribute__((used)) static const char *dio_getname(int id)
{
        /* return pointer to a constant string describing the board with given ID */
	unsigned int i;
	for (i = 0; i < ARRAY_SIZE(names); i++)
                if (names[i].id == id) 
                        return names[i].name;

        return unknowndioname;
}