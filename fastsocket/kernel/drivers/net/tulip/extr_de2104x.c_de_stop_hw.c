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
struct de_private {scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ rx_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  MacStatus ; 
 int /*<<< orphan*/  de_stop_rxtx (struct de_private*) ; 
 int /*<<< orphan*/  dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void de_stop_hw (struct de_private *de)
{

	udelay(5);
	dw32(IntrMask, 0);

	de_stop_rxtx(de);

	dw32(MacStatus, dr32(MacStatus));

	udelay(10);

	de->rx_tail = 0;
	de->tx_head = de->tx_tail = 0;
}