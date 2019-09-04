#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hostcache_prune_data {int cache_timeout; int /*<<< orphan*/  now; } ;
struct connectdata {struct Curl_easy* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  hostcache; } ;
struct TYPE_5__ {int dns_cache_timeout; } ;
struct TYPE_4__ {scalar_t__ wildcard_resolve; } ;
struct Curl_easy {TYPE_3__ dns; TYPE_2__ set; TYPE_1__ change; } ;
struct Curl_dns_entry {int dummy; } ;
typedef  int /*<<< orphan*/  entry_id ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_hash_delete (int /*<<< orphan*/ ,char*,size_t) ; 
 struct Curl_dns_entry* Curl_hash_pick (int /*<<< orphan*/ ,char*,size_t) ; 
 int MAX_HOSTCACHE_LEN ; 
 int /*<<< orphan*/  create_hostcache_id (char const*,int,char*,int) ; 
 scalar_t__ hostcache_timestamp_remove (struct hostcache_prune_data*,struct Curl_dns_entry*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct Curl_dns_entry *
fetch_addr(struct connectdata *conn,
                const char *hostname,
                int port)
{
  struct Curl_dns_entry *dns = NULL;
  size_t entry_len;
  struct Curl_easy *data = conn->data;
  char entry_id[MAX_HOSTCACHE_LEN];

  /* Create an entry id, based upon the hostname and port */
  create_hostcache_id(hostname, port, entry_id, sizeof(entry_id));
  entry_len = strlen(entry_id);

  /* See if its already in our dns cache */
  dns = Curl_hash_pick(data->dns.hostcache, entry_id, entry_len + 1);

  /* No entry found in cache, check if we might have a wildcard entry */
  if(!dns && data->change.wildcard_resolve) {
    create_hostcache_id("*", port, entry_id, sizeof(entry_id));
    entry_len = strlen(entry_id);

    /* See if it's already in our dns cache */
    dns = Curl_hash_pick(data->dns.hostcache, entry_id, entry_len + 1);
  }

  if(dns && (data->set.dns_cache_timeout != -1)) {
    /* See whether the returned entry is stale. Done before we release lock */
    struct hostcache_prune_data user;

    time(&user.now);
    user.cache_timeout = data->set.dns_cache_timeout;

    if(hostcache_timestamp_remove(&user, dns)) {
      infof(data, "Hostname in DNS cache was stale, zapped\n");
      dns = NULL; /* the memory deallocation is being handled by the hash */
      Curl_hash_delete(data->dns.hostcache, entry_id, entry_len + 1);
    }
  }

  return dns;
}