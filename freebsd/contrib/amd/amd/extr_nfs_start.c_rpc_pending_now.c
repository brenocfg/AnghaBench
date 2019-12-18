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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwd_sock ; 
 int select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
rpc_pending_now(void)
{
  struct timeval tvv;
  int nsel;
  fd_set readfds;

  FD_ZERO(&readfds);
  FD_SET(fwd_sock, &readfds);

  tvv.tv_sec = tvv.tv_usec = 0;
  nsel = select(FD_SETSIZE, &readfds, (fd_set *) NULL, (fd_set *) NULL, &tvv);
  if (nsel < 1)
    return (0);
  if (FD_ISSET(fwd_sock, &readfds))
    return (1);

  return (0);
}