#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  dispname; } ;
struct TYPE_13__ {int /*<<< orphan*/  dispname; } ;
struct TYPE_16__ {scalar_t__ conn_to_host; scalar_t__ httpproxy; scalar_t__ socksproxy; } ;
struct TYPE_11__ {int /*<<< orphan*/  dispname; } ;
struct TYPE_12__ {TYPE_2__ host; } ;
struct TYPE_17__ {int /*<<< orphan*/  dispname; } ;
struct TYPE_10__ {TYPE_8__ host; } ;
struct connectdata {int /*<<< orphan*/  connection_id; int /*<<< orphan*/  port; int /*<<< orphan*/  ip_addr_str; TYPE_5__ host; TYPE_4__ conn_to_host; TYPE_7__ bits; TYPE_3__ http_proxy; TYPE_1__ socks_proxy; TYPE_9__* data; } ;
struct TYPE_15__ {scalar_t__ verbose; } ;
struct TYPE_18__ {TYPE_6__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  infof (TYPE_9__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Curl_verboseconnect(struct connectdata *conn)
{
  if(conn->data->set.verbose)
    infof(conn->data, "Connected to %s (%s) port %ld (#%ld)\n",
          conn->bits.socksproxy ? conn->socks_proxy.host.dispname :
          conn->bits.httpproxy ? conn->http_proxy.host.dispname :
          conn->bits.conn_to_host ? conn->conn_to_host.dispname :
          conn->host.dispname,
          conn->ip_addr_str, conn->port, conn->connection_id);
}