#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int ip_addr; int ip_mask; struct TYPE_3__* ip_next; } ;
typedef  TYPE_1__ addrlist ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  inet_dquad (char*,int,int) ; 
 TYPE_1__* localnets ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
islocalnet(u_long addr)
{
  addrlist *al;

  for (al = localnets; al; al = al->ip_next)
    if (((addr ^ al->ip_addr) & al->ip_mask) == 0)
      return TRUE;

#ifdef DEBUG
  {
    char buf[16];
    plog(XLOG_INFO, "%s is on a remote network",
	 inet_dquad(buf, sizeof(buf), addr));
  }
#endif /* DEBUG */

  return FALSE;
}