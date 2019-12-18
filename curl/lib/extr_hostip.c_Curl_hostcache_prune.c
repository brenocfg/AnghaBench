#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int dns_cache_timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  hostcache; } ;
struct Curl_easy {scalar_t__ share; TYPE_2__ set; TYPE_1__ dns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_DNS ; 
 int /*<<< orphan*/  Curl_share_lock (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_unlock (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostcache_prune (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void Curl_hostcache_prune(struct Curl_easy *data)
{
  time_t now;

  if((data->set.dns_cache_timeout == -1) || !data->dns.hostcache)
    /* cache forever means never prune, and NULL hostcache means
       we can't do it */
    return;

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  time(&now);

  /* Remove outdated and unused entries from the hostcache */
  hostcache_prune(data->dns.hostcache,
                  data->set.dns_cache_timeout,
                  now);

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
}