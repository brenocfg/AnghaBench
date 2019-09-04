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
struct hostcache_prune_data {scalar_t__ now; scalar_t__ cache_timeout; } ;
struct Curl_dns_entry {scalar_t__ timestamp; } ;

/* Variables and functions */

__attribute__((used)) static int
hostcache_timestamp_remove(void *datap, void *hc)
{
  struct hostcache_prune_data *data =
    (struct hostcache_prune_data *) datap;
  struct Curl_dns_entry *c = (struct Curl_dns_entry *) hc;

  return (0 != c->timestamp)
    && (data->now - c->timestamp >= data->cache_timeout);
}