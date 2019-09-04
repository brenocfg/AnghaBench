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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  socket_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_set_traffic_mgt_flags_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_unlock (int /*<<< orphan*/ ,int) ; 

void
socket_set_traffic_mgt_flags(socket_t sock, u_int8_t flags)
{
	socket_lock(sock, 1);
	socket_set_traffic_mgt_flags_locked(sock, flags);
	socket_unlock(sock, 1);
}