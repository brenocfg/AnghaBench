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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tipc_port_unlock(struct port *p_ptr)
{
	spin_unlock_bh(p_ptr->publ.lock);
}