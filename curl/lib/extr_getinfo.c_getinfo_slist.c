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
struct curl_tlssessioninfo {int /*<<< orphan*/ * internals; int /*<<< orphan*/  backend; } ;
struct curl_slist {int dummy; } ;
struct curl_certinfo {int dummy; } ;
struct connectdata {TYPE_2__* ssl; } ;
struct TYPE_4__ {struct curl_certinfo certs; } ;
struct Curl_easy {struct connectdata* conn; struct curl_tlssessioninfo tsi; TYPE_1__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* get_internals ) (TYPE_2__*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  use; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int CURLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNKNOWN_OPTION ; 
#define  CURLINFO_CERTINFO 132 
#define  CURLINFO_COOKIELIST 131 
#define  CURLINFO_SSL_ENGINES 130 
#define  CURLINFO_TLS_SESSION 129 
#define  CURLINFO_TLS_SSL_PTR 128 
 int /*<<< orphan*/  CURLSSLBACKEND_NONE ; 
 struct curl_slist* Curl_cookie_list (struct Curl_easy*) ; 
 TYPE_3__* Curl_ssl ; 
 int /*<<< orphan*/  Curl_ssl_backend () ; 
 struct curl_slist* Curl_ssl_engines_list (struct Curl_easy*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static CURLcode getinfo_slist(struct Curl_easy *data, CURLINFO info,
                              struct curl_slist **param_slistp)
{
  union {
    struct curl_certinfo *to_certinfo;
    struct curl_slist    *to_slist;
  } ptr;

  switch(info) {
  case CURLINFO_SSL_ENGINES:
    *param_slistp = Curl_ssl_engines_list(data);
    break;
  case CURLINFO_COOKIELIST:
    *param_slistp = Curl_cookie_list(data);
    break;
  case CURLINFO_CERTINFO:
    /* Return the a pointer to the certinfo struct. Not really an slist
       pointer but we can pretend it is here */
    ptr.to_certinfo = &data->info.certs;
    *param_slistp = ptr.to_slist;
    break;
  case CURLINFO_TLS_SESSION:
  case CURLINFO_TLS_SSL_PTR:
    {
      struct curl_tlssessioninfo **tsip = (struct curl_tlssessioninfo **)
                                          param_slistp;
      struct curl_tlssessioninfo *tsi = &data->tsi;
#ifdef USE_SSL
      struct connectdata *conn = data->conn;
#endif

      *tsip = tsi;
      tsi->backend = Curl_ssl_backend();
      tsi->internals = NULL;

#ifdef USE_SSL
      if(conn && tsi->backend != CURLSSLBACKEND_NONE) {
        unsigned int i;
        for(i = 0; i < (sizeof(conn->ssl) / sizeof(conn->ssl[0])); ++i) {
          if(conn->ssl[i].use) {
            tsi->internals = Curl_ssl->get_internals(&conn->ssl[i], info);
            break;
          }
        }
      }
#endif
    }
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}