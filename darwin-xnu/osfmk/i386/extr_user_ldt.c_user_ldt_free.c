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
typedef  TYPE_1__* user_ldt_t ;
struct user_ldt {int dummy; } ;
struct real_descriptor {int dummy; } ;
struct TYPE_4__ {int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 

void
user_ldt_free(
	user_ldt_t	user_ldt)
{
	kfree(user_ldt, sizeof(struct user_ldt) + (user_ldt->count * sizeof(struct real_descriptor)));
}