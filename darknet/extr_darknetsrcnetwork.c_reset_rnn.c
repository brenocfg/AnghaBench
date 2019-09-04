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
typedef  int /*<<< orphan*/  network ;

/* Variables and functions */
 int /*<<< orphan*/  reset_network_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void reset_rnn(network *net)
{
    reset_network_state(net, 0);
}