#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct lguest {TYPE_1__* lguest_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  syscall_vec; } ;

/* Variables and functions */
 int could_be_syscall (int /*<<< orphan*/ ) ; 
 scalar_t__ get_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool check_syscall_vector(struct lguest *lg)
{
	u32 vector;

	if (get_user(vector, &lg->lguest_data->syscall_vec))
		return false;

	return could_be_syscall(vector);
}