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
typedef  int /*<<< orphan*/  ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ip_set_put_byindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_lock () ; 
 int /*<<< orphan*/  nfnl_unlock () ; 

void
ip_set_nfnl_put(ip_set_id_t index)
{
	nfnl_lock();
	ip_set_put_byindex(index);
	nfnl_unlock();
}