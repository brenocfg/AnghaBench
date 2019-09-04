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
struct connectdata {TYPE_2__* data; } ;
struct Curl_dns_entry {int dummy; } ;
struct TYPE_3__ {scalar_t__ doh; } ;
struct TYPE_4__ {TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_doh_is_resolved (struct connectdata*,struct Curl_dns_entry**) ; 
 int /*<<< orphan*/  Curl_resolver_is_resolved (struct connectdata*,struct Curl_dns_entry**) ; 

CURLcode Curl_resolv_check(struct connectdata *conn,
                           struct Curl_dns_entry **dns)
{
  if(conn->data->set.doh)
    return Curl_doh_is_resolved(conn, dns);
  return Curl_resolver_is_resolved(conn, dns);
}