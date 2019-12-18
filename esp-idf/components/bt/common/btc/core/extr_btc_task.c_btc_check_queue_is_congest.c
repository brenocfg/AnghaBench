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

/* Variables and functions */
 scalar_t__ BT_QUEUE_CONGEST_SIZE ; 
 int /*<<< orphan*/  btc_thread ; 
 scalar_t__ osi_thread_queue_wait_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool btc_check_queue_is_congest(void)
{
    if (osi_thread_queue_wait_size(btc_thread, 0) >= BT_QUEUE_CONGEST_SIZE) {
        return true;
    }

    return false;
}