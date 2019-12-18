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
typedef  scalar_t__ apr_uint32_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_memcache_t ;
typedef  int /*<<< orphan*/  apr_memcache_server_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  PORT ; 
 scalar_t__ TDATA_SET ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  apr_itoa (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  apr_memcache_add_multget_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_add_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_delete (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_memcache_multgetp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_server_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_set (int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ apr_pool_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_test_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p ; 
 int /*<<< orphan*/  prefix ; 
 int /*<<< orphan*/  strlen (void*) ; 

__attribute__((used)) static void test_memcache_multiget(abts_case * tc, void *data)
{
  apr_pool_t *pool = p;
  apr_pool_t *tmppool;
  apr_status_t rv;
  apr_memcache_t *memcache;
  apr_memcache_server_t *server;
  apr_hash_t *tdata, *values;
  apr_hash_index_t *hi;
  apr_uint32_t i;

  rv = apr_memcache_create(pool, 1, 0, &memcache);
  ABTS_ASSERT(tc, "memcache create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_server_create(pool, HOST, PORT, 0, 1, 1, 60, &server);
  ABTS_ASSERT(tc, "server create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_add_server(memcache, server);
  ABTS_ASSERT(tc, "server add failed", rv == APR_SUCCESS);
  
  values = apr_hash_make(p);
  tdata = apr_hash_make(p);
  
  create_test_hash(pool, tdata);

  for (hi = apr_hash_first(p, tdata); hi; hi = apr_hash_next(hi)) {
    const void *k;
    void *v;
    const char *key;

    apr_hash_this(hi, &k, NULL, &v);
    key = k;

    rv = apr_memcache_set(memcache, key, v, strlen(v), 0, 27);
    ABTS_ASSERT(tc, "set failed", rv == APR_SUCCESS);
  }
  
  rv = apr_pool_create(&tmppool, pool);
  for (i = 0; i < TDATA_SET; i++)
    apr_memcache_add_multget_key(pool,
                                 apr_pstrcat(pool, prefix,
                                             apr_itoa(pool, i), NULL),
                                 &values);
    
  rv = apr_memcache_multgetp(memcache,
                             tmppool,
                             pool,
                             values);
  
  ABTS_ASSERT(tc, "multgetp failed", rv == APR_SUCCESS);
  ABTS_ASSERT(tc, "multgetp returned too few results",
              apr_hash_count(values) == TDATA_SET);
  
  for (hi = apr_hash_first(p, tdata); hi; hi = apr_hash_next(hi)) {
    const void *k;
    const char *key;
    
    apr_hash_this(hi, &k, NULL, NULL);
    key = k;

    rv = apr_memcache_delete(memcache, key, 0);
    ABTS_ASSERT(tc, "delete failed", rv == APR_SUCCESS);
  }
  
}