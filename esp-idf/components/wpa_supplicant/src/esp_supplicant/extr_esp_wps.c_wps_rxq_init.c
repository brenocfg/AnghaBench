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
 int /*<<< orphan*/  DATA_MUTEX_GIVE () ; 
 int /*<<< orphan*/  DATA_MUTEX_TAKE () ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_wps_rxq ; 

__attribute__((used)) static void wps_rxq_init(void)
{
    DATA_MUTEX_TAKE();
    STAILQ_INIT(&s_wps_rxq);
    DATA_MUTEX_GIVE();
}