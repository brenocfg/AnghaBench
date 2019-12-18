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
struct sky2_rx_le {scalar_t__ ctrl; } ;
struct sky2_port {int rx_put; struct sky2_rx_le* rx_le; } ;

/* Variables and functions */
 int RING_NEXT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_LE_SIZE ; 

__attribute__((used)) static inline struct sky2_rx_le *sky2_next_rx(struct sky2_port *sky2)
{
	struct sky2_rx_le *le = sky2->rx_le + sky2->rx_put;
	sky2->rx_put = RING_NEXT(sky2->rx_put, RX_LE_SIZE);
	le->ctrl = 0;
	return le;
}