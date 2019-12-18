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
typedef  int /*<<< orphan*/  future_t ;
typedef  size_t btc_main_future_type_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** main_future ; 

future_t **btc_main_get_future_p(btc_main_future_type_t type)
{
    return &main_future[type];
}