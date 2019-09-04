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
struct Sockets {int count; int /*<<< orphan*/ * sockets; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notifyCurl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char const*) ; 

__attribute__((used)) static void checkFdSet(CURLM *curl, struct Sockets *sockets, fd_set *fdset,
                       int evBitmask, const char *name)
{
  int i;
  for(i = 0; i < sockets->count; ++i) {
    if(FD_ISSET(sockets->sockets[i], fdset)) {
      notifyCurl(curl, sockets->sockets[i], evBitmask, name);
    }
  }
}