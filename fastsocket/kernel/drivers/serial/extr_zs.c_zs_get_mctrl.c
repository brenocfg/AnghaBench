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
struct zs_scc {int /*<<< orphan*/  zlock; } ;
struct zs_port {struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 unsigned int zs_raw_get_mctrl (struct zs_port*) ; 

__attribute__((used)) static unsigned int zs_get_mctrl(struct uart_port *uport)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	unsigned int mctrl;

	spin_lock(&scc->zlock);
	mctrl = zs_raw_get_mctrl(zport);
	spin_unlock(&scc->zlock);

	return mctrl;
}