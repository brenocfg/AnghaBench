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
typedef  scalar_t__ ACResult ;
typedef  int ACIpAddress ;

/* Variables and functions */
 scalar_t__ ACGetAssignedAddress (int*) ; 
 scalar_t__ ACGetAssignedSubnet (int*) ; 

int getBroadcastAddress(ACIpAddress *broadcast)
{
   ACIpAddress myIp, mySubnet;
   ACResult result;

   if(broadcast == NULL)
      return -1;

   result = ACGetAssignedAddress(&myIp);
   if(result < 0)
      return -1;
   result = ACGetAssignedSubnet(&mySubnet);
   if(result < 0)
      return -1;

   *broadcast = myIp | (~mySubnet);
   return 0;
}