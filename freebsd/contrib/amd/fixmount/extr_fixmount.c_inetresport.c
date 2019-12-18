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
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EADDRINUSE ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int IPPORT_RESERVED ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
inetresport(int ty)
{
  int alport;
  struct sockaddr_in addr;
  int fd;

  memset(&addr, 0, sizeof(addr));
  /* as per POSIX, sin_len need not be set (used internally by kernel) */

  addr.sin_family = AF_INET;	/* use internet address family */
  addr.sin_addr.s_addr = INADDR_ANY;
  if ((fd = socket(AF_INET, ty, 0)) < 0)
    return -1;

  for (alport = IPPORT_RESERVED - 1; alport > IPPORT_RESERVED / 2 + 1; alport--) {
    addr.sin_port = htons((u_short) alport);
    if (bind(fd, (struct sockaddr *) &addr, sizeof(addr)) >= 0)
      return fd;
    if (errno != EADDRINUSE) {
      close(fd);
      return -1;
    }
  }
  close(fd);
  errno = EAGAIN;
  return -1;
}