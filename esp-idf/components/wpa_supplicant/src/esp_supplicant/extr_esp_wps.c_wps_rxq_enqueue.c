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
struct wps_rx_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_MUTEX_GIVE () ; 
 int /*<<< orphan*/  DATA_MUTEX_TAKE () ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct wps_rx_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bqentry ; 
 int /*<<< orphan*/  s_wps_rxq ; 

__attribute__((used)) static void wps_rxq_enqueue(struct wps_rx_param *param)
{
    DATA_MUTEX_TAKE();
    STAILQ_INSERT_TAIL(&s_wps_rxq,param, bqentry);
    DATA_MUTEX_GIVE();
}