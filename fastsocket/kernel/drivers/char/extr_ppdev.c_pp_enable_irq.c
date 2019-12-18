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
struct pp_struct {TYPE_1__* pdev; } ;
struct parport {TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_irq ) (struct parport*) ;} ;
struct TYPE_3__ {struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct parport*) ; 

__attribute__((used)) static inline void pp_enable_irq (struct pp_struct *pp)
{
	struct parport *port = pp->pdev->port;
	port->ops->enable_irq (port);
}