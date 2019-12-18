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
typedef  int /*<<< orphan*/  socket_t ;
typedef  int /*<<< orphan*/  sflt_handle ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  sflt_attach_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_unlock (int /*<<< orphan*/ ,int) ; 

errno_t
sflt_attach(socket_t socket, sflt_handle handle)
{
	socket_lock(socket, 1);
	errno_t result = sflt_attach_internal(socket, handle);
	socket_unlock(socket, 1);
	return (result);
}