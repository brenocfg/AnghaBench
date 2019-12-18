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
typedef  int /*<<< orphan*/  SOCKET_T ;

/* Variables and functions */
 size_t DEFAULT_MAXIMUM_DATAGRAM_SIZE ; 

size_t vc_container_net_private_maximum_datagram_size( SOCKET_T sock )
{
   (void)sock;

   /* No easy way to determine this, just use the default. */
   return DEFAULT_MAXIMUM_DATAGRAM_SIZE;
}