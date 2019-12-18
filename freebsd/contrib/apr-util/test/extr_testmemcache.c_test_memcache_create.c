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
typedef  scalar_t__ apr_port_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_memcache_t ;
typedef  int /*<<< orphan*/  apr_memcache_server_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ABTS_PTR_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ABTS_PTR_NOTNULL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  HOST ; 
 scalar_t__ PORT ; 
 scalar_t__ apr_memcache_add_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_create (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ apr_memcache_disable_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_memcache_enable_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_memcache_find_server (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * apr_memcache_find_server_hash (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ apr_memcache_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_memcache_server_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * p ; 
 int /*<<< orphan*/  prefix ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_memcache_create(abts_case * tc, void *data)
{
  apr_pool_t *pool = p;
  apr_status_t rv;
  apr_memcache_t *memcache;
  apr_memcache_server_t *server, *s;
  apr_uint32_t max_servers = 10;
  apr_uint32_t i;
  apr_uint32_t hash;

  rv = apr_memcache_create(pool, max_servers, 0, &memcache);
  ABTS_ASSERT(tc, "memcache create failed", rv == APR_SUCCESS);
  
  for (i = 1; i <= max_servers; i++) {
    apr_port_t port;
    
    port = PORT + i;
    rv =
      apr_memcache_server_create(pool, HOST, PORT + i, 0, 1, 1, 60, &server);
    ABTS_ASSERT(tc, "server create failed", rv == APR_SUCCESS);
    
    rv = apr_memcache_add_server(memcache, server);
    ABTS_ASSERT(tc, "server add failed", rv == APR_SUCCESS);
    
    s = apr_memcache_find_server(memcache, HOST, port);
    ABTS_PTR_EQUAL(tc, server, s);
    
    rv = apr_memcache_disable_server(memcache, s);
    ABTS_ASSERT(tc, "server disable failed", rv == APR_SUCCESS);
    
    rv = apr_memcache_enable_server(memcache, s);
    ABTS_ASSERT(tc, "server enable failed", rv == APR_SUCCESS);
    
    hash = apr_memcache_hash(memcache, prefix, strlen(prefix));
    ABTS_ASSERT(tc, "hash failed", hash > 0);
    
    s = apr_memcache_find_server_hash(memcache, hash);
    ABTS_PTR_NOTNULL(tc, s);
  }

  rv = apr_memcache_server_create(pool, HOST, PORT, 0, 1, 1, 60, &server);
  ABTS_ASSERT(tc, "server create failed", rv == APR_SUCCESS);
  
  rv = apr_memcache_add_server(memcache, server);
  ABTS_ASSERT(tc, "server add should have failed", rv != APR_SUCCESS);
  
}