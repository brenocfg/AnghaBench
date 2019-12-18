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
typedef  int in_addr_t ;

/* Variables and functions */
 int inet_addr (char*) ; 

bool validateIpAddress(char* ip) {
  in_addr_t ipAddr = inet_addr(ip);
  return (ipAddr != 0) && (ipAddr != 0xffffffff);
}