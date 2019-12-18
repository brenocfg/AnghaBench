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
struct uart_pmac_port {int flags; struct uart_pmac_port* mate; } ;

/* Variables and functions */
 int PMACZILOG_FLAG_IS_CHANNEL_A ; 

__attribute__((used)) static inline struct uart_pmac_port *pmz_get_port_A(struct uart_pmac_port *uap)
{
	if (uap->flags & PMACZILOG_FLAG_IS_CHANNEL_A)
		return uap;
	return uap->mate;
}