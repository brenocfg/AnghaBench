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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

bool socket_bind(int fd, void *data)
{
   int yes               = 1;
   struct addrinfo *res  = (struct addrinfo*)data;
   setsockopt(fd, SOL_SOCKET,
         SO_REUSEADDR, (const char*)&yes, sizeof(int));
   if (bind(fd, res->ai_addr, res->ai_addrlen) < 0)
      return false;
   return true;
}