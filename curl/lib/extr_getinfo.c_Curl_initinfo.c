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
struct PureInfo {int filetime; char* conn_primary_ip; char* conn_local_ip; scalar_t__ conn_protocol; scalar_t__ conn_scheme; scalar_t__ conn_local_port; scalar_t__ conn_primary_port; int /*<<< orphan*/ * wouldredirect; int /*<<< orphan*/ * contenttype; scalar_t__ numconnects; scalar_t__ httpauthavail; scalar_t__ proxyauthavail; scalar_t__ request_size; scalar_t__ header_size; int /*<<< orphan*/  timecond; scalar_t__ httpversion; scalar_t__ httpproxycode; scalar_t__ httpcode; } ;
struct Progress {int is_t_startransfer_set; scalar_t__ t_redirect; scalar_t__ timespent; scalar_t__ t_starttransfer; scalar_t__ t_pretransfer; scalar_t__ t_appconnect; scalar_t__ t_connect; scalar_t__ t_nslookup; } ;
struct Curl_easy {struct PureInfo info; struct Progress progress; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_ssl_free_certinfo (struct Curl_easy*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

CURLcode Curl_initinfo(struct Curl_easy *data)
{
  struct Progress *pro = &data->progress;
  struct PureInfo *info = &data->info;

  pro->t_nslookup = 0;
  pro->t_connect = 0;
  pro->t_appconnect = 0;
  pro->t_pretransfer = 0;
  pro->t_starttransfer = 0;
  pro->timespent = 0;
  pro->t_redirect = 0;
  pro->is_t_startransfer_set = false;

  info->httpcode = 0;
  info->httpproxycode = 0;
  info->httpversion = 0;
  info->filetime = -1; /* -1 is an illegal time and thus means unknown */
  info->timecond = FALSE;

  info->header_size = 0;
  info->request_size = 0;
  info->proxyauthavail = 0;
  info->httpauthavail = 0;
  info->numconnects = 0;

  free(info->contenttype);
  info->contenttype = NULL;

  free(info->wouldredirect);
  info->wouldredirect = NULL;

  info->conn_primary_ip[0] = '\0';
  info->conn_local_ip[0] = '\0';
  info->conn_primary_port = 0;
  info->conn_local_port = 0;

  info->conn_scheme = 0;
  info->conn_protocol = 0;

#ifdef USE_SSL
  Curl_ssl_free_certinfo(data);
#endif
  return CURLE_OK;
}