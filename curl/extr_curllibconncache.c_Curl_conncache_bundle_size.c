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
struct connectdata {int /*<<< orphan*/  data; TYPE_1__* bundle; } ;
struct TYPE_2__ {size_t num_connections; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONN_UNLOCK (int /*<<< orphan*/ ) ; 

size_t Curl_conncache_bundle_size(struct connectdata *conn)
{
  size_t num;
  CONN_LOCK(conn->data);
  num = conn->bundle->num_connections;
  CONN_UNLOCK(conn->data);
  return num;
}