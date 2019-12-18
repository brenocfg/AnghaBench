#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {scalar_t__ nat_traversal; scalar_t__ is_server; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_tcp_socket (TYPE_1__*,void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_init_nat_traversal (TYPE_1__*) ; 
 int /*<<< orphan*/  network_init () ; 

__attribute__((used)) static bool init_socket(netplay_t *netplay, void *direct_host,
      const char *server, uint16_t port)
{
   if (!network_init())
      return false;

   if (!init_tcp_socket(netplay, direct_host, server, port))
      return false;

   if (netplay->is_server && netplay->nat_traversal)
      netplay_init_nat_traversal(netplay);

   return true;
}