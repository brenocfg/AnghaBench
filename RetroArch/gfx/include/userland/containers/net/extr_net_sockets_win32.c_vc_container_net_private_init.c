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
typedef  int /*<<< orphan*/  vc_container_net_status_t ;
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_SUCCESS ; 
 int WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translate_error_status (int) ; 

vc_container_net_status_t vc_container_net_private_init()
{
   WSADATA wsa_data;
   int result;

   result = WSAStartup(MAKEWORD(2,2), &wsa_data);
   if (result)
      return translate_error_status( result );

   return VC_CONTAINER_NET_SUCCESS;
}