#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dohentry {int dummy; } ;
struct TYPE_12__ {struct Curl_dns_entry* dns; int /*<<< orphan*/  hostname; } ;
struct TYPE_7__ {scalar_t__ proxy; } ;
struct connectdata {TYPE_6__ async; TYPE_1__ bits; struct Curl_easy* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  port; int /*<<< orphan*/  host; TYPE_3__* probe; int /*<<< orphan*/  pending; } ;
struct TYPE_11__ {TYPE_4__ doh; } ;
struct Curl_easy {scalar_t__ share; TYPE_5__ req; int /*<<< orphan*/  multi; } ;
struct Curl_dns_entry {int dummy; } ;
struct Curl_addrinfo {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  memory; int /*<<< orphan*/  size; } ;
struct TYPE_9__ {int /*<<< orphan*/  dnstype; TYPE_2__ serverdoh; int /*<<< orphan*/  easy; } ;
typedef  scalar_t__ DOHcode ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_COULDNT_RESOLVE_HOST ; 
 int /*<<< orphan*/  CURLE_COULDNT_RESOLVE_PROXY ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURL_LOCK_ACCESS_SINGLE ; 
 int /*<<< orphan*/  CURL_LOCK_DATA_DNS ; 
 struct Curl_dns_entry* Curl_cache_addr (struct Curl_easy*,struct Curl_addrinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_freeaddrinfo (struct Curl_addrinfo*) ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_lock (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_share_unlock (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de_cleanup (struct dohentry*) ; 
 struct Curl_addrinfo* doh2ai (struct dohentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ doh_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dohentry*) ; 
 int /*<<< orphan*/  doh_strerror (scalar_t__) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  init_dohentry (struct dohentry*) ; 
 int /*<<< orphan*/  showdoh (struct Curl_easy*,struct dohentry*) ; 
 int /*<<< orphan*/  type2name (int /*<<< orphan*/ ) ; 

CURLcode Curl_doh_is_resolved(struct connectdata *conn,
                              struct Curl_dns_entry **dnsp)
{
  struct Curl_easy *data = conn->data;
  *dnsp = NULL; /* defaults to no response */

  if(!data->req.doh.probe[0].easy && !data->req.doh.probe[1].easy) {
    failf(data, "Could not DOH-resolve: %s", conn->async.hostname);
    return conn->bits.proxy?CURLE_COULDNT_RESOLVE_PROXY:
      CURLE_COULDNT_RESOLVE_HOST;
  }
  else if(!data->req.doh.pending) {
    DOHcode rc;
    DOHcode rc2;
    struct dohentry de;
    /* remove DOH handles from multi handle and close them */
    curl_multi_remove_handle(data->multi, data->req.doh.probe[0].easy);
    Curl_close(&data->req.doh.probe[0].easy);
    curl_multi_remove_handle(data->multi, data->req.doh.probe[1].easy);
    Curl_close(&data->req.doh.probe[1].easy);
    /* parse the responses, create the struct and return it! */
    init_dohentry(&de);
    rc = doh_decode(data->req.doh.probe[0].serverdoh.memory,
                    data->req.doh.probe[0].serverdoh.size,
                    data->req.doh.probe[0].dnstype,
                    &de);
    Curl_safefree(data->req.doh.probe[0].serverdoh.memory);
    if(rc) {
      infof(data, "DOH: %s type %s for %s\n", doh_strerror(rc),
            type2name(data->req.doh.probe[0].dnstype),
            data->req.doh.host);
    }
    rc2 = doh_decode(data->req.doh.probe[1].serverdoh.memory,
                     data->req.doh.probe[1].serverdoh.size,
                     data->req.doh.probe[1].dnstype,
                     &de);
    Curl_safefree(data->req.doh.probe[1].serverdoh.memory);
    if(rc2) {
      infof(data, "DOH: %s type %s for %s\n", doh_strerror(rc2),
            type2name(data->req.doh.probe[1].dnstype),
            data->req.doh.host);
    }
    if(!rc || !rc2) {
      struct Curl_dns_entry *dns;
      struct Curl_addrinfo *ai;

      infof(data, "DOH Host name: %s\n", data->req.doh.host);
      showdoh(data, &de);

      ai = doh2ai(&de, data->req.doh.host, data->req.doh.port);
      if(!ai) {
        de_cleanup(&de);
        return CURLE_OUT_OF_MEMORY;
      }

      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      /* we got a response, store it in the cache */
      dns = Curl_cache_addr(data, ai, data->req.doh.host, data->req.doh.port);

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);

      de_cleanup(&de);
      if(!dns)
        /* returned failure, bail out nicely */
        Curl_freeaddrinfo(ai);
      else {
        conn->async.dns = dns;
        *dnsp = dns;
        return CURLE_OK;
      }
    }
    de_cleanup(&de);

    return CURLE_COULDNT_RESOLVE_HOST;
  }

  return CURLE_OK;
}