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
struct connectdata {int /*<<< orphan*/ * data; struct connectbundle* bundle; } ;
struct connectbundle {scalar_t__ num_connections; } ;
struct conncache {int /*<<< orphan*/  num_conn; } ;
struct TYPE_2__ {struct conncache* conn_cache; } ;
struct Curl_easy {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_LOCK (struct Curl_easy*) ; 
 int /*<<< orphan*/  CONN_UNLOCK (struct Curl_easy*) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_remove_conn (struct connectbundle*,struct connectdata*) ; 
 int /*<<< orphan*/  conncache_remove_bundle (struct conncache*,struct connectbundle*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 

void Curl_conncache_remove_conn(struct Curl_easy *data,
                                struct connectdata *conn, bool lock)
{
  struct connectbundle *bundle = conn->bundle;
  struct conncache *connc = data->state.conn_cache;

  /* The bundle pointer can be NULL, since this function can be called
     due to a failed connection attempt, before being added to a bundle */
  if(bundle) {
    if(lock) {
      CONN_LOCK(data);
    }
    bundle_remove_conn(bundle, conn);
    if(bundle->num_connections == 0)
      conncache_remove_bundle(connc, bundle);
    conn->bundle = NULL; /* removed from it */
    if(connc) {
      connc->num_conn--;
      DEBUGF(infof(data, "The cache now contains %zu members\n",
                   connc->num_conn));
    }
    conn->data = NULL; /* clear the association */
    if(lock) {
      CONN_UNLOCK(data);
    }
  }
}