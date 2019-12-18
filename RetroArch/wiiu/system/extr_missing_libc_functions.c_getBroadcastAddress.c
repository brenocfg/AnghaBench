#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;

/* Variables and functions */

__attribute__((used)) static int getBroadcastAddress(struct sockaddr_in *sa, struct sockaddr_in *addr, struct sockaddr_in *mask)
{
   if (!sa || !addr || !mask)
      return -1;

   sa->sin_addr.s_addr = addr->sin_addr.s_addr | (~mask->sin_addr.s_addr);
   return 0;
}