#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dohdata {int dummy; } ;
struct connectdata {scalar_t__ ip_version; struct Curl_easy* data; } ;
struct TYPE_7__ {char const* host; int port; TYPE_4__* probe; int /*<<< orphan*/ * headers; int /*<<< orphan*/  pending; } ;
struct TYPE_6__ {TYPE_3__ doh; } ;
struct TYPE_5__ {int /*<<< orphan*/ * str; } ;
struct Curl_easy {TYPE_2__ req; int /*<<< orphan*/  multi; TYPE_1__ set; } ;
struct TYPE_8__ {int /*<<< orphan*/  easy; } ;
typedef  int /*<<< orphan*/  Curl_addrinfo ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURL_IPRESOLVE_V4 ; 
 scalar_t__ CURL_IPRESOLVE_V6 ; 
 int /*<<< orphan*/  Curl_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DNS_TYPE_A ; 
 int /*<<< orphan*/  DNS_TYPE_AAAA ; 
 size_t STRING_DOH ; 
 int TRUE ; 
 int /*<<< orphan*/ * curl_slist_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  curl_slist_free_all (int /*<<< orphan*/ *) ; 
 scalar_t__ dohprobe (struct Curl_easy*,TYPE_4__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

Curl_addrinfo *Curl_doh(struct connectdata *conn,
                        const char *hostname,
                        int port,
                        int *waitp)
{
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;
  *waitp = TRUE; /* this never returns synchronously */
  (void)conn;
  (void)hostname;
  (void)port;

  /* start clean, consider allocating this struct on demand */
  memset(&data->req.doh, 0, sizeof(struct dohdata));

  data->req.doh.host = hostname;
  data->req.doh.port = port;
  data->req.doh.headers =
    curl_slist_append(NULL,
                      "Content-Type: application/dns-message");
  if(!data->req.doh.headers)
    goto error;

  if(conn->ip_version != CURL_IPRESOLVE_V6) {
    /* create IPv4 DOH request */
    result = dohprobe(data, &data->req.doh.probe[0], DNS_TYPE_A,
                      hostname, data->set.str[STRING_DOH],
                      data->multi, data->req.doh.headers);
    if(result)
      goto error;
    data->req.doh.pending++;
  }

  if(conn->ip_version != CURL_IPRESOLVE_V4) {
    /* create IPv6 DOH request */
    result = dohprobe(data, &data->req.doh.probe[1], DNS_TYPE_AAAA,
                      hostname, data->set.str[STRING_DOH],
                      data->multi, data->req.doh.headers);
    if(result)
      goto error;
    data->req.doh.pending++;
  }
  return NULL;

  error:
  curl_slist_free_all(data->req.doh.headers);
  data->req.doh.headers = NULL;
  Curl_close(&data->req.doh.probe[0].easy);
  Curl_close(&data->req.doh.probe[1].easy);
  return NULL;
}