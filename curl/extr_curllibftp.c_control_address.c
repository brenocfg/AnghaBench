#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {scalar_t__ socksproxy; scalar_t__ tunnel_proxy; } ;
struct connectdata {char* ip_addr_str; TYPE_2__ host; TYPE_1__ bits; } ;

/* Variables and functions */

__attribute__((used)) static char *control_address(struct connectdata *conn)
{
  /* Returns the control connection IP address.
     If a proxy tunnel is used, returns the original host name instead, because
     the effective control connection address is the proxy address,
     not the ftp host. */
  if(conn->bits.tunnel_proxy || conn->bits.socksproxy)
    return conn->host.name;

  return conn->ip_addr_str;
}