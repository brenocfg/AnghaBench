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
struct pcmcia_socket {TYPE_1__* resource_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 

void release_resource_db(struct pcmcia_socket *s)
{
	if (s->resource_ops->exit)
		s->resource_ops->exit(s);
}