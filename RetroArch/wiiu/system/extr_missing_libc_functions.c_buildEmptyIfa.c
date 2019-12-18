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
struct sockaddr_in {int dummy; } ;
struct sockaddr {void* sa_family; struct sockaddr* ifa_dstaddr; struct sockaddr* ifa_netmask; struct sockaddr* ifa_addr; int /*<<< orphan*/  ifa_name; } ;
struct ifaddrs {void* sa_family; struct ifaddrs* ifa_dstaddr; struct ifaddrs* ifa_netmask; struct ifaddrs* ifa_addr; int /*<<< orphan*/  ifa_name; } ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  freeifaddrs (struct sockaddr*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiiu_iface_name ; 

__attribute__((used)) static struct ifaddrs *buildEmptyIfa(void)
{
   struct ifaddrs *result = (struct ifaddrs *)malloc(sizeof(struct ifaddrs));
   if (result)
   {
      memset(result, 0, sizeof(struct ifaddrs));
      result->ifa_name = strdup(wiiu_iface_name);
      result->ifa_addr = (struct sockaddr *)malloc(sizeof(struct sockaddr_in));
      result->ifa_netmask = (struct sockaddr *)malloc(sizeof(struct sockaddr_in));
      result->ifa_dstaddr = (struct sockaddr *)malloc(sizeof(struct sockaddr_in));

      if (!result->ifa_name || !result->ifa_addr || !result->ifa_netmask || !result->ifa_dstaddr)
         goto error;

      memset(result->ifa_addr, 0, sizeof(struct sockaddr_in));
      result->ifa_addr->sa_family = AF_INET;
      memset(result->ifa_netmask, 0, sizeof(struct sockaddr_in));
      result->ifa_netmask->sa_family = AF_INET;
      memset(result->ifa_dstaddr, 0, sizeof(struct sockaddr_in));
      result->ifa_dstaddr->sa_family = AF_INET;
   }

   return result;
error:
   freeifaddrs(result);
   return NULL;
}