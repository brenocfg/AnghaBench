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
typedef  int /*<<< orphan*/  SocketInfoRef ;

/* Variables and functions */
 int /*<<< orphan*/  bind_sockets (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void *
second_thread(void * arg)
{
	SocketInfoRef	info = (SocketInfoRef)arg;

	bind_sockets(info, "second");
	return (NULL);
}