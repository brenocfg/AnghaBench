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
struct gameport {int dummy; } ;
struct adi_port {int /*<<< orphan*/  reads; int /*<<< orphan*/  bad; } ;

/* Variables and functions */
 scalar_t__ adi_read (struct adi_port*) ; 
 struct adi_port* gameport_get_drvdata (struct gameport*) ; 

__attribute__((used)) static void adi_poll(struct gameport *gameport)
{
	struct adi_port *port = gameport_get_drvdata(gameport);

	port->bad -= adi_read(port);
	port->reads++;
}