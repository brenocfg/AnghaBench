#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {int /*<<< orphan*/  h_addr; } ;
typedef  TYPE_1__* mountlist ;
typedef  int /*<<< orphan*/  hostaddr ;
struct TYPE_4__ {int /*<<< orphan*/  ml_directory; int /*<<< orphan*/  ml_hostname; struct TYPE_4__* ml_next; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  fixmount_check_mount (char*,struct in_addr,int /*<<< orphan*/ ) ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ is_same_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_mount (int /*<<< orphan*/ *,char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  thisaddr ; 
 int /*<<< orphan*/  thishost ; 

void
fix_rmtab(CLIENT *client, char *host, mountlist mp, int fixit, int force)
{
  mountlist p;
  struct hostent *he;
  struct in_addr hostaddr;

  /*
   * Obtain remote address for comparisons
   */
  if ((he = gethostbyname(host))) {
    memcpy(&hostaddr, he->h_addr, sizeof(hostaddr));
  } else {
    hostaddr.s_addr = INADDR_NONE;
  }

  for (p = mp; p; p = p->ml_next) {
    if (is_same_host(p->ml_hostname, thishost, thisaddr)) {
      if (force || !fixmount_check_mount(host, hostaddr, p->ml_directory))
	remove_mount(client, host, p, fixit);
    }
  }
}