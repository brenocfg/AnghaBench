#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int /*<<< orphan*/  local_port; TYPE_3__* data; int /*<<< orphan*/  primary_port; TYPE_1__* handler; int /*<<< orphan*/  local_ip; int /*<<< orphan*/  primary_ip; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn_local_port; int /*<<< orphan*/  conn_primary_port; int /*<<< orphan*/  conn_protocol; int /*<<< orphan*/  conn_scheme; int /*<<< orphan*/  conn_local_ip; int /*<<< orphan*/  conn_primary_ip; } ;
struct TYPE_6__ {TYPE_2__ info; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocol; int /*<<< orphan*/  scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_IPADR_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Curl_persistconninfo(struct connectdata *conn)
{
  memcpy(conn->data->info.conn_primary_ip, conn->primary_ip, MAX_IPADR_LEN);
  memcpy(conn->data->info.conn_local_ip, conn->local_ip, MAX_IPADR_LEN);
  conn->data->info.conn_scheme = conn->handler->scheme;
  conn->data->info.conn_protocol = conn->handler->protocol;
  conn->data->info.conn_primary_port = conn->primary_port;
  conn->data->info.conn_local_port = conn->local_port;
}