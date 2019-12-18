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
typedef  int apr_uint32_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_memcache_t ;
typedef  int /*<<< orphan*/  apr_memcache_server_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ABTS_INT_EQUAL (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  PORT ; 
 int TDATA_SIZE ; 
 scalar_t__ apr_memcache_add_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_decr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ apr_memcache_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_memcache_getp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ apr_memcache_server_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/ * p ; 
 int /*<<< orphan*/  prefix ; 

__attribute__((used)) static void test_memcache_incrdecr(abts_case * tc, void *data)
{
 apr_pool_t *pool = p;
 apr_status_t rv;
 apr_memcache_t *memcache;
 apr_memcache_server_t *server;
 apr_uint32_t new;
 char *result;
 apr_size_t len;
 apr_uint32_t i;

  rv = apr_memcache_create(pool, 1, 0, &memcache);
  ABTS_ASSERT(tc, "memcache create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_server_create(pool, HOST, PORT, 0, 1, 1, 60, &server);
  ABTS_ASSERT(tc, "server create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_add_server(memcache, server);
  ABTS_ASSERT(tc, "server add failed", rv == APR_SUCCESS);

  rv = apr_memcache_set(memcache, prefix, "271", sizeof("271") - 1, 0, 27);
  ABTS_ASSERT(tc, "set failed", rv == APR_SUCCESS);
  
  for( i = 1; i <= TDATA_SIZE; i++) {
    apr_uint32_t expect;

    rv = apr_memcache_getp(memcache, pool, prefix, &result, &len, NULL);
    ABTS_ASSERT(tc, "get failed", rv == APR_SUCCESS);

    expect = i + atoi(result);

    rv = apr_memcache_incr(memcache, prefix, i, &new);
    ABTS_ASSERT(tc, "incr failed", rv == APR_SUCCESS);

    ABTS_INT_EQUAL(tc, expect, new);

    rv = apr_memcache_decr(memcache, prefix, i, &new);
    ABTS_ASSERT(tc, "decr failed", rv == APR_SUCCESS);
    ABTS_INT_EQUAL(tc, atoi(result), new);

  }

  rv = apr_memcache_getp(memcache, pool, prefix, &result, &len, NULL);
  ABTS_ASSERT(tc, "get failed", rv == APR_SUCCESS);

  ABTS_INT_EQUAL(tc, 271, atoi(result));

  rv = apr_memcache_delete(memcache, prefix, 0);
  ABTS_ASSERT(tc, "delete failed", rv == APR_SUCCESS);
}