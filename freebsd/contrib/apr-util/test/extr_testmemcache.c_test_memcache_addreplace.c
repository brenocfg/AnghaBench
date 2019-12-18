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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_memcache_t ;
typedef  int /*<<< orphan*/  apr_memcache_server_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ABTS_STR_NEQUAL (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  PORT ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ apr_memcache_add (int /*<<< orphan*/ *,char const*,void*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ apr_memcache_add_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_delete (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_memcache_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_replace (int /*<<< orphan*/ *,char const*,char*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ apr_memcache_server_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_test_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p ; 
 scalar_t__ strlen (void*) ; 

__attribute__((used)) static void test_memcache_addreplace(abts_case * tc, void *data)
{
 apr_pool_t *pool = p;
 apr_status_t rv;
 apr_memcache_t *memcache;
 apr_memcache_server_t *server;
 apr_hash_t *tdata;
 apr_hash_index_t *hi;
 char *result;
 apr_size_t len;

  rv = apr_memcache_create(pool, 1, 0, &memcache);
  ABTS_ASSERT(tc, "memcache create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_server_create(pool, HOST, PORT, 0, 1, 1, 60, &server);
  ABTS_ASSERT(tc, "server create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_add_server(memcache, server);
  ABTS_ASSERT(tc, "server add failed", rv == APR_SUCCESS);
  
  tdata = apr_hash_make(p);
  create_test_hash(pool, tdata);

  for (hi = apr_hash_first(p, tdata); hi; hi = apr_hash_next(hi)) {
    const void *k;
    void *v;
    const char *key;

    apr_hash_this(hi, &k, NULL, &v);
    key = k;

    /* doesn't exist yet, fail */
    rv = apr_memcache_replace(memcache, key, v, strlen(v) - 1, 0, 27);
    ABTS_ASSERT(tc, "replace should have failed", rv != APR_SUCCESS);
    
    /* doesn't exist yet, succeed */
    rv = apr_memcache_add(memcache, key, v, strlen(v), 0, 27);
    ABTS_ASSERT(tc, "add failed", rv == APR_SUCCESS);

    /* exists now, succeed */
    rv = apr_memcache_replace(memcache, key, "new", sizeof("new") - 1, 0, 27);
    ABTS_ASSERT(tc, "replace failed", rv == APR_SUCCESS);

    /* make sure its different */
    rv = apr_memcache_getp(memcache, pool, key, &result, &len, NULL);
    ABTS_ASSERT(tc, "get failed", rv == APR_SUCCESS);
    ABTS_STR_NEQUAL(tc, result, "new", 3);

    /* exists now, fail */
    rv = apr_memcache_add(memcache, key, v, strlen(v), 0, 27);
    ABTS_ASSERT(tc, "add should have failed", rv != APR_SUCCESS);

    /* clean up */
    rv = apr_memcache_delete(memcache, key, 0);
    ABTS_ASSERT(tc, "delete failed", rv == APR_SUCCESS);
  }
}