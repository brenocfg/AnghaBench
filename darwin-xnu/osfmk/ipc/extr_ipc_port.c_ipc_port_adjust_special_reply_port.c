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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_adjust_special_reply_port_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipc_port_adjust_special_reply_port(
	ipc_port_t special_reply_port,
	uint8_t flags,
	boolean_t get_turnstile)
{
	ip_lock(special_reply_port);
	ipc_port_adjust_special_reply_port_locked(special_reply_port, NULL, flags, get_turnstile);
	/* special_reply_port unlocked */
}