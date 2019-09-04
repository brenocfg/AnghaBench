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
struct Curl_easy {scalar_t__ share; } ;
struct Curl_dns_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_DNS ; 
 int /*<<< orphan*/  Curl_share_lock (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_unlock (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freednsentry (struct Curl_dns_entry*) ; 

void Curl_resolv_unlock(struct Curl_easy *data, struct Curl_dns_entry *dns)
{
  if(data && data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  freednsentry(dns);

  if(data && data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
}