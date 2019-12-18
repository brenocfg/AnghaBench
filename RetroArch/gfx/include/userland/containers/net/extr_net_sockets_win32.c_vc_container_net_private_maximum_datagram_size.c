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
typedef  int /*<<< orphan*/  max_datagram_size ;
typedef  int /*<<< orphan*/  SOCKET_T ;

/* Variables and functions */
 size_t DEFAULT_MAXIMUM_DATAGRAM_SIZE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

size_t vc_container_net_private_maximum_datagram_size( SOCKET_T sock )
{
   size_t max_datagram_size = DEFAULT_MAXIMUM_DATAGRAM_SIZE;
   int opt_size = sizeof(max_datagram_size);

   /* Ignore errors and use the default if necessary */
   (void)getsockopt(sock, SOL_SOCKET, SO_MAX_MSG_SIZE, (char *)&max_datagram_size, &opt_size);

   return max_datagram_size;
}