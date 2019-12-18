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
struct tport {int dummy; } ;
struct inet_port {int (* activate ) (struct inet_port*) ;} ;

/* Variables and functions */
 int stub1 (struct inet_port*) ; 

__attribute__((used)) static int
inet_activate(struct tport *tp)
{
	struct inet_port *port = (struct inet_port *)tp;

	return (port->activate(port));
}