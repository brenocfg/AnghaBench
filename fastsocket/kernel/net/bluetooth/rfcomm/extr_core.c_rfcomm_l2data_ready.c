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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int) ; 
 int /*<<< orphan*/  RFCOMM_SCHED_RX ; 
 int /*<<< orphan*/  rfcomm_schedule (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rfcomm_l2data_ready(struct sock *sk, int bytes)
{
	BT_DBG("%p bytes %d", sk, bytes);
	rfcomm_schedule(RFCOMM_SCHED_RX);
}