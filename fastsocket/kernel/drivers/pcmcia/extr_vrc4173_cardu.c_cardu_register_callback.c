#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void (* handler ) (void*,unsigned int) ;void* info; } ;
typedef  TYPE_1__ vrc4173_socket_t ;

/* Variables and functions */
 TYPE_1__* cardu_sockets ; 

__attribute__((used)) static int cardu_register_callback(unsigned int sock,
                                           void (*handler)(void *, unsigned int),
                                           void * info)
{
	vrc4173_socket_t *socket = &cardu_sockets[sock];

	socket->handler = handler;
	socket->info = info;

	return 0;
}