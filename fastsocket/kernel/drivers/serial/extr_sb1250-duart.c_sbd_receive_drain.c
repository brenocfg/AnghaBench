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
struct sbd_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_DUART_RX_HOLD ; 
 int /*<<< orphan*/  read_sbdchn (struct sbd_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ sbd_receive_ready (struct sbd_port*) ; 

__attribute__((used)) static int sbd_receive_drain(struct sbd_port *sport)
{
	int loops = 10000;

	while (sbd_receive_ready(sport) && --loops)
		read_sbdchn(sport, R_DUART_RX_HOLD);
	return loops;
}