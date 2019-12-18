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
struct TYPE_2__ {int /*<<< orphan*/ * rx_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_queue_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ hci_hal_env ; 
 int /*<<< orphan*/  osi_free_func ; 

__attribute__((used)) static void hci_hal_env_deinit(void)
{
    fixed_queue_free(hci_hal_env.rx_q, osi_free_func);
    hci_hal_env.rx_q = NULL;
}