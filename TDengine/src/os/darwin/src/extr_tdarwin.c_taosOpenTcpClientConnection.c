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

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tError (char*) ; 

void *taosOpenTcpClientConnection(void *shandle, void *thandle, char *ip, short port) {
  tError("function taosOpenTcpClientConnection is not implemented in darwin system, exit!");
  exit(0);
}