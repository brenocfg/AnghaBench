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
struct resource {int dummy; } ;
struct pcmcia_socket {TYPE_1__* resource_ops; } ;
struct TYPE_2__ {struct resource* (* find_io ) (unsigned long,int,unsigned long,struct pcmcia_socket*) ;} ;

/* Variables and functions */
 struct resource* stub1 (unsigned long,int,unsigned long,struct pcmcia_socket*) ; 

struct resource *pcmcia_find_io_region(unsigned long base, int num,
		   unsigned long align, struct pcmcia_socket *s)
{
	if (s->resource_ops->find_io)
		return s->resource_ops->find_io(base, num, align, s);
	return NULL;
}