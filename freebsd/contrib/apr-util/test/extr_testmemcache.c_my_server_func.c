#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ which_server; } ;
typedef  TYPE_1__ my_hash_server_baton ;
typedef  int /*<<< orphan*/  apr_uint32_t ;
struct TYPE_5__ {scalar_t__ ntotal; int /*<<< orphan*/ ** live_servers; } ;
typedef  TYPE_2__ apr_memcache_t ;
typedef  int /*<<< orphan*/  apr_memcache_server_t ;

/* Variables and functions */

__attribute__((used)) static apr_memcache_server_t *my_server_func(void *baton, 
                                             apr_memcache_t *mc,
                                             const apr_uint32_t hash)
{
  apr_memcache_server_t *ms = NULL;
  my_hash_server_baton *mhsb = (my_hash_server_baton *)baton;

  if(mc->ntotal == 0) {
    return NULL;
  } 

  if(mc->ntotal < mhsb->which_server) {
    return NULL;
  }

  ms = mc->live_servers[mhsb->which_server - 1];

  return ms;
}