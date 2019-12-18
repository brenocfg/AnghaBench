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

/* Variables and functions */
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  translate_error_status (int /*<<< orphan*/ ) ; 

vc_container_net_status_t vc_container_net_private_last_error()
{
   return translate_error_status( WSAGetLastError() );
}