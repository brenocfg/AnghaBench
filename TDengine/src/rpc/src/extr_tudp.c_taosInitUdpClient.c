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
 void* taosInitUdpConnection (char*,short,char*,int,void*,void*) ; 

void *taosInitUdpClient(char *ip, short port, char *label, int threads, void *fp, void *shandle) {
  return taosInitUdpConnection(ip, port, label, threads, fp, shandle);
}