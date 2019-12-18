#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rmt_tx_end_fn_t ;
struct TYPE_4__ {void* arg; int /*<<< orphan*/  function; } ;
typedef  TYPE_1__ rmt_tx_end_callback_t ;

/* Variables and functions */
 TYPE_1__ rmt_tx_end_callback ; 

rmt_tx_end_callback_t rmt_register_tx_end_callback(rmt_tx_end_fn_t function, void *arg)
{
    rmt_tx_end_callback_t previous = rmt_tx_end_callback;
    rmt_tx_end_callback.function = function;
    rmt_tx_end_callback.arg = arg;
    return previous;
}