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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_container_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_clear_address(struct sockaddr *p_addr)
{
   switch (p_addr->sa_family)
   {
   case AF_INET:
      {
         struct sockaddr_in *p_addr_v4 = (struct sockaddr_in *)p_addr;

         memset(&p_addr_v4->sin_addr, 0, sizeof(p_addr_v4->sin_addr));
      }
      break;
   case AF_INET6:
      {
         struct sockaddr_in6 *p_addr_v6 = (struct sockaddr_in6 *)p_addr;

         memset(&p_addr_v6->sin6_addr, 0, sizeof(p_addr_v6->sin6_addr));
      }
      break;
   default:
      /* Invalid or unsupported address family */
      vc_container_assert(0);
   }
}