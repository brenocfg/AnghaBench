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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMACZILOG_FLAG_TX_STOPPED ; 
 TYPE_1__* to_pmz (struct uart_port*) ; 

__attribute__((used)) static void pmz_stop_tx(struct uart_port *port)
{
	to_pmz(port)->flags |= PMACZILOG_FLAG_TX_STOPPED;
}