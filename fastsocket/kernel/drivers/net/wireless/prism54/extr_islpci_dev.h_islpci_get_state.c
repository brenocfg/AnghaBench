#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  islpci_state_t ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */

__attribute__((used)) static inline islpci_state_t
islpci_get_state(islpci_private *priv)
{
	/* lock */
	return priv->state;
	/* unlock */
}