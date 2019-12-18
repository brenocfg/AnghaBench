#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct curl_slist {char* data; struct curl_slist* next; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {scalar_t__ te; scalar_t__ host; } ;
struct TYPE_6__ {scalar_t__ authneg; int /*<<< orphan*/  tunnel_proxy; scalar_t__ httpproxy; } ;
struct connectdata {int httpversion; TYPE_5__ host; TYPE_2__ allocptr; TYPE_1__ bits; struct Curl_easy* data; } ;
struct TYPE_9__ {scalar_t__ first_host; scalar_t__ this_is_a_follow; } ;
struct TYPE_8__ {scalar_t__ httpreq; int /*<<< orphan*/  allow_auth_to_other_hosts; struct curl_slist* headers; struct curl_slist* proxyheaders; int /*<<< orphan*/  sep_headers; } ;
struct Curl_easy {TYPE_4__ state; TYPE_3__ set; } ;
typedef  enum proxy_use { ____Placeholder_proxy_use } proxy_use ;
typedef  int /*<<< orphan*/  Curl_send_buffer ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_add_buffer_free (int /*<<< orphan*/ **) ; 
 scalar_t__ Curl_add_bufferf (int /*<<< orphan*/ **,char*,char*) ; 
#define  HEADER_CONNECT 130 
#define  HEADER_PROXY 129 
#define  HEADER_SERVER 128 
 scalar_t__ HTTPREQ_POST_FORM ; 
 scalar_t__ HTTPREQ_POST_MIME ; 
 scalar_t__ ISSPACE (char) ; 
 scalar_t__ checkprefix (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcasecompare (scalar_t__,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 

CURLcode Curl_add_custom_headers(struct connectdata *conn,
                                 bool is_connect,
                                 Curl_send_buffer *req_buffer)
{
  char *ptr;
  struct curl_slist *h[2];
  struct curl_slist *headers;
  int numlists = 1; /* by default */
  struct Curl_easy *data = conn->data;
  int i;

  enum proxy_use proxy;

  if(is_connect)
    proxy = HEADER_CONNECT;
  else
    proxy = conn->bits.httpproxy && !conn->bits.tunnel_proxy?
      HEADER_PROXY:HEADER_SERVER;

  switch(proxy) {
  case HEADER_SERVER:
    h[0] = data->set.headers;
    break;
  case HEADER_PROXY:
    h[0] = data->set.headers;
    if(data->set.sep_headers) {
      h[1] = data->set.proxyheaders;
      numlists++;
    }
    break;
  case HEADER_CONNECT:
    if(data->set.sep_headers)
      h[0] = data->set.proxyheaders;
    else
      h[0] = data->set.headers;
    break;
  }

  /* loop through one or two lists */
  for(i = 0; i < numlists; i++) {
    headers = h[i];

    while(headers) {
      char *semicolonp = NULL;
      ptr = strchr(headers->data, ':');
      if(!ptr) {
        char *optr;
        /* no colon, semicolon? */
        ptr = strchr(headers->data, ';');
        if(ptr) {
          optr = ptr;
          ptr++; /* pass the semicolon */
          while(*ptr && ISSPACE(*ptr))
            ptr++;

          if(*ptr) {
            /* this may be used for something else in the future */
            optr = NULL;
          }
          else {
            if(*(--ptr) == ';') {
              /* copy the source */
              semicolonp = strdup(headers->data);
              if(!semicolonp) {
                Curl_add_buffer_free(&req_buffer);
                return CURLE_OUT_OF_MEMORY;
              }
              /* put a colon where the semicolon is */
              semicolonp[ptr - headers->data] = ':';
              /* point at the colon */
              optr = &semicolonp [ptr - headers->data];
            }
          }
          ptr = optr;
        }
      }
      if(ptr) {
        /* we require a colon for this to be a true header */

        ptr++; /* pass the colon */
        while(*ptr && ISSPACE(*ptr))
          ptr++;

        if(*ptr || semicolonp) {
          /* only send this if the contents was non-blank or done special */
          CURLcode result = CURLE_OK;
          char *compare = semicolonp ? semicolonp : headers->data;

          if(conn->allocptr.host &&
             /* a Host: header was sent already, don't pass on any custom Host:
                header as that will produce *two* in the same request! */
             checkprefix("Host:", compare))
            ;
          else if(data->set.httpreq == HTTPREQ_POST_FORM &&
                  /* this header (extended by formdata.c) is sent later */
                  checkprefix("Content-Type:", compare))
            ;
          else if(data->set.httpreq == HTTPREQ_POST_MIME &&
                  /* this header is sent later */
                  checkprefix("Content-Type:", compare))
            ;
          else if(conn->bits.authneg &&
                  /* while doing auth neg, don't allow the custom length since
                     we will force length zero then */
                  checkprefix("Content-Length:", compare))
            ;
          else if(conn->allocptr.te &&
                  /* when asking for Transfer-Encoding, don't pass on a custom
                     Connection: */
                  checkprefix("Connection:", compare))
            ;
          else if((conn->httpversion >= 20) &&
                  checkprefix("Transfer-Encoding:", compare))
            /* HTTP/2 doesn't support chunked requests */
            ;
          else if((checkprefix("Authorization:", compare) ||
                   checkprefix("Cookie:", compare)) &&
                  /* be careful of sending this potentially sensitive header to
                     other hosts */
                  (data->state.this_is_a_follow &&
                   data->state.first_host &&
                   !data->set.allow_auth_to_other_hosts &&
                   !strcasecompare(data->state.first_host, conn->host.name)))
            ;
          else {
            result = Curl_add_bufferf(&req_buffer, "%s\r\n", compare);
          }
          if(semicolonp)
            free(semicolonp);
          if(result)
            return result;
        }
      }
      headers = headers->next;
    }
  }

  return CURLE_OK;
}