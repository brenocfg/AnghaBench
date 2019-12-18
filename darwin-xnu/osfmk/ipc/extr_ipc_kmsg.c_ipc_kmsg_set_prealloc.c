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
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  TYPE_1__* ipc_kmsg_t ;
struct TYPE_4__ {scalar_t__ ikm_prealloc; scalar_t__ ikm_turnstile; } ;

/* Variables and functions */
 scalar_t__ IP_NULL ; 
 int /*<<< orphan*/  IP_SET_PREALLOC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ TURNSTILE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ port_send_turnstile (int /*<<< orphan*/ ) ; 

void
ipc_kmsg_set_prealloc(
	ipc_kmsg_t		kmsg,
	ipc_port_t		port)
{
	assert(kmsg->ikm_prealloc == IP_NULL);
  
	kmsg->ikm_prealloc = IP_NULL;

	assert(port_send_turnstile(port) == TURNSTILE_NULL);
	kmsg->ikm_turnstile = TURNSTILE_NULL;
	IP_SET_PREALLOC(port, kmsg);
}