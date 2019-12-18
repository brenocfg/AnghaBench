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
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int FALSE ; 
 int SOCKET_READABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 

__attribute__((used)) static bool SocketIsDead(curl_socket_t sock)
{
  int sval;
  bool ret_val = TRUE;

  sval = SOCKET_READABLE(sock, 0);
  if(sval == 0)
    /* timeout */
    ret_val = FALSE;

  return ret_val;
}