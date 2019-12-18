#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  upcb; } ;
struct TYPE_4__ {TYPE_1__ machine; } ;

/* Variables and functions */
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/  get_saved_state_pc (int /*<<< orphan*/ ) ; 

user_addr_t
get_useraddr()
{
	return (get_saved_state_pc(current_thread()->machine.upcb));
}