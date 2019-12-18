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
struct connectdata {int /*<<< orphan*/  data; } ;
struct connectbundle {int dummy; } ;
struct conncache {int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_LOCK (int /*<<< orphan*/ ) ; 
 struct connectbundle* Curl_hash_pick (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int HASHKEY_SIZE ; 
 int /*<<< orphan*/  hashkey (struct connectdata*,char*,int,char const**) ; 
 int /*<<< orphan*/  strlen (char*) ; 

struct connectbundle *Curl_conncache_find_bundle(struct connectdata *conn,
                                                 struct conncache *connc,
                                                 const char **hostp)
{
  struct connectbundle *bundle = NULL;
  CONN_LOCK(conn->data);
  if(connc) {
    char key[HASHKEY_SIZE];
    hashkey(conn, key, sizeof(key), hostp);
    bundle = Curl_hash_pick(&connc->hash, key, strlen(key));
  }

  return bundle;
}