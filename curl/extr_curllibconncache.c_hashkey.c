#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* name; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_14__ {scalar_t__ conn_to_host; scalar_t__ httpproxy; scalar_t__ socksproxy; } ;
struct TYPE_8__ {char* name; } ;
struct TYPE_9__ {TYPE_1__ host; } ;
struct TYPE_12__ {char* name; } ;
struct TYPE_13__ {TYPE_5__ host; } ;
struct connectdata {int /*<<< orphan*/  port; TYPE_4__ host; TYPE_3__ conn_to_host; TYPE_7__ bits; TYPE_2__ http_proxy; TYPE_6__ socks_proxy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  msnprintf (char*,size_t,char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void hashkey(struct connectdata *conn, char *buf,
                    size_t len) /* something like 128 is fine */
{
  const char *hostname;

  if(conn->bits.socksproxy)
    hostname = conn->socks_proxy.host.name;
  else if(conn->bits.httpproxy)
    hostname = conn->http_proxy.host.name;
  else if(conn->bits.conn_to_host)
    hostname = conn->conn_to_host.name;
  else
    hostname = conn->host.name;

  DEBUGASSERT(len > 32);

  /* put the number first so that the hostname gets cut off if too long */
  msnprintf(buf, len, "%ld%s", conn->port, hostname);
}