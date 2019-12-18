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
struct connectdata {scalar_t__ connection_id; struct Curl_easy* data; } ;
struct connectbundle {int dummy; } ;
struct conncache {int /*<<< orphan*/  num_conn; int /*<<< orphan*/  next_connection_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn_cache; } ;
struct Curl_easy {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  key ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_UNLOCK (struct Curl_easy*) ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 struct connectbundle* Curl_conncache_find_bundle (struct connectdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int HASHKEY_SIZE ; 
 int /*<<< orphan*/  bundle_add_conn (struct connectbundle*,struct connectdata*) ; 
 scalar_t__ bundle_create (struct Curl_easy*,struct connectbundle**) ; 
 int /*<<< orphan*/  bundle_destroy (struct connectbundle*) ; 
 int conncache_add_bundle (int /*<<< orphan*/ ,char*,struct connectbundle*) ; 
 int /*<<< orphan*/  hashkey (struct connectdata*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,scalar_t__,int /*<<< orphan*/ ) ; 

CURLcode Curl_conncache_add_conn(struct conncache *connc,
                                 struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct connectbundle *bundle;
  struct connectbundle *new_bundle = NULL;
  struct Curl_easy *data = conn->data;

  /* *find_bundle() locks the connection cache */
  bundle = Curl_conncache_find_bundle(conn, data->state.conn_cache, NULL);
  if(!bundle) {
    int rc;
    char key[HASHKEY_SIZE];

    result = bundle_create(data, &new_bundle);
    if(result) {
      goto unlock;
    }

    hashkey(conn, key, sizeof(key), NULL);
    rc = conncache_add_bundle(data->state.conn_cache, key, new_bundle);

    if(!rc) {
      bundle_destroy(new_bundle);
      result = CURLE_OUT_OF_MEMORY;
      goto unlock;
    }
    bundle = new_bundle;
  }

  bundle_add_conn(bundle, conn);
  conn->connection_id = connc->next_connection_id++;
  connc->num_conn++;

  DEBUGF(infof(conn->data, "Added connection %ld. "
               "The cache now contains %zu members\n",
               conn->connection_id, connc->num_conn));

  unlock:
  CONN_UNLOCK(data);

  return result;
}