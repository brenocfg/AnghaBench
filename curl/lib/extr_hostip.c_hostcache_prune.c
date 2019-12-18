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
typedef  int /*<<< orphan*/  time_t ;
struct hostcache_prune_data {long cache_timeout; int /*<<< orphan*/  now; } ;
struct curl_hash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_hash_clean_with_criterium (struct curl_hash*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostcache_timestamp_remove ; 

__attribute__((used)) static void
hostcache_prune(struct curl_hash *hostcache, long cache_timeout, time_t now)
{
  struct hostcache_prune_data user;

  user.cache_timeout = cache_timeout;
  user.now = now;

  Curl_hash_clean_with_criterium(hostcache,
                                 (void *) &user,
                                 hostcache_timestamp_remove);
}