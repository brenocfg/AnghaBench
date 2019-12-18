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
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ svc_getcaller (int /*<<< orphan*/ *) ; 

struct sockaddr_in *
amu_svc_getcaller(SVCXPRT *xprt)
{
  /* glibc 2.2 returns a sockaddr_storage ??? */
  return (struct sockaddr_in *) svc_getcaller(xprt);
}