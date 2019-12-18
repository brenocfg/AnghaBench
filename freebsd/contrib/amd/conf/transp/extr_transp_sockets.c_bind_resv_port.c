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
typedef  int /*<<< orphan*/  voidp ;
typedef  scalar_t__ u_short ;
struct sockaddr_in {void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int IPPORT_RESERVED ; 
 int bind (int,struct sockaddr*,int) ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
bind_resv_port(int so, u_short *pp)
{
  struct sockaddr_in sin;
  int rc;
  u_short port;

  memset((voidp) &sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;

  if (pp && *pp > 0) {
    sin.sin_port = htons(*pp);
    rc = bind(so, (struct sockaddr *) &sin, sizeof(sin));
  } else {
    port = IPPORT_RESERVED;

    do {
      --port;
      sin.sin_port = htons(port);
      rc = bind(so, (struct sockaddr *) &sin, sizeof(sin));
    } while (rc < 0 && (int) port > IPPORT_RESERVED / 2);

    if (pp && rc == 0)
      *pp = port;
  }

  return rc;
}