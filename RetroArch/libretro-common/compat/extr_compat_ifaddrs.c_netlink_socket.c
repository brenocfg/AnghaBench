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
struct sockaddr_nl {int /*<<< orphan*/  nl_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  l_addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 int /*<<< orphan*/  NETLINK_ROUTE ; 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_nl*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlink_socket(void)
{
   struct sockaddr_nl l_addr;
   int l_socket = socket(PF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

   if(l_socket < 0)
      return -1;

   memset(&l_addr, 0, sizeof(l_addr));
   l_addr.nl_family = AF_NETLINK;
   if(bind(l_socket, (struct sockaddr *)&l_addr, sizeof(l_addr)) < 0)
   {
      close(l_socket);
      return -1;
   }

   return l_socket;
}