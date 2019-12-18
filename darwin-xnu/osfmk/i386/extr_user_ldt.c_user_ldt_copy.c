#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* user_ldt_t ;
struct user_ldt {int dummy; } ;
struct real_descriptor {int dummy; } ;
struct TYPE_6__ {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  kalloc (size_t) ; 

user_ldt_t
user_ldt_copy(
	user_ldt_t	user_ldt)
{
	if (user_ldt != NULL) {
	    size_t	size = sizeof(struct user_ldt) + (user_ldt->count * sizeof(struct real_descriptor));
	    user_ldt_t	new_ldt = (user_ldt_t)kalloc(size);
	    if (new_ldt != NULL)
		bcopy(user_ldt, new_ldt, size);
	    return new_ldt;
	}
	
	return 0;
}