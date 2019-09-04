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
struct TYPE_4__ {TYPE_1__* conn_cache; } ;
struct Curl_easy {TYPE_2__ state; } ;
struct TYPE_3__ {size_t num_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_LOCK (struct Curl_easy*) ; 
 int /*<<< orphan*/  CONN_UNLOCK (struct Curl_easy*) ; 

size_t Curl_conncache_size(struct Curl_easy *data)
{
  size_t num;
  CONN_LOCK(data);
  num = data->state.conn_cache->num_conn;
  CONN_UNLOCK(data);
  return num;
}