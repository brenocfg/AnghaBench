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
struct TYPE_10__ {long httpcode; long httpproxycode; long filetime; unsigned long httpauthavail; unsigned long proxyauthavail; long numconnects; long conn_primary_port; long conn_local_port; long conn_protocol; int /*<<< orphan*/  httpversion; int /*<<< orphan*/  timecond; scalar_t__ request_size; scalar_t__ header_size; } ;
struct TYPE_9__ {long os_errno; long rtsp_next_client_CSeq; long rtsp_next_server_CSeq; long rtsp_CSeq_recv; } ;
struct TYPE_7__ {long certverifyresult; } ;
struct TYPE_6__ {long certverifyresult; } ;
struct TYPE_8__ {long followlocation; TYPE_2__ proxy_ssl; TYPE_1__ ssl; } ;
struct Curl_easy {TYPE_5__ info; TYPE_4__ state; TYPE_3__ set; } ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int CURLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNKNOWN_OPTION ; 
#define  CURLINFO_CONDITION_UNMET 148 
#define  CURLINFO_FILETIME 147 
#define  CURLINFO_HEADER_SIZE 146 
#define  CURLINFO_HTTPAUTH_AVAIL 145 
#define  CURLINFO_HTTP_CONNECTCODE 144 
#define  CURLINFO_HTTP_VERSION 143 
#define  CURLINFO_LASTSOCKET 142 
#define  CURLINFO_LOCAL_PORT 141 
#define  CURLINFO_NUM_CONNECTS 140 
#define  CURLINFO_OS_ERRNO 139 
#define  CURLINFO_PRIMARY_PORT 138 
#define  CURLINFO_PROTOCOL 137 
#define  CURLINFO_PROXYAUTH_AVAIL 136 
#define  CURLINFO_PROXY_SSL_VERIFYRESULT 135 
#define  CURLINFO_REDIRECT_COUNT 134 
#define  CURLINFO_REQUEST_SIZE 133 
#define  CURLINFO_RESPONSE_CODE 132 
#define  CURLINFO_RTSP_CLIENT_CSEQ 131 
#define  CURLINFO_RTSP_CSEQ_RECV 130 
#define  CURLINFO_RTSP_SERVER_CSEQ 129 
#define  CURLINFO_SSL_VERIFYRESULT 128 
 long CURL_HTTP_VERSION_1_0 ; 
 long CURL_HTTP_VERSION_1_1 ; 
 long CURL_HTTP_VERSION_2_0 ; 
 long CURL_HTTP_VERSION_3 ; 
 long CURL_HTTP_VERSION_NONE ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 scalar_t__ Curl_getconnectinfo (struct Curl_easy*,int /*<<< orphan*/ *) ; 
 long LONG_MAX ; 
 long LONG_MIN ; 

__attribute__((used)) static CURLcode getinfo_long(struct Curl_easy *data, CURLINFO info,
                             long *param_longp)
{
  curl_socket_t sockfd;

  union {
    unsigned long *to_ulong;
    long          *to_long;
  } lptr;

  switch(info) {
  case CURLINFO_RESPONSE_CODE:
    *param_longp = data->info.httpcode;
    break;
  case CURLINFO_HTTP_CONNECTCODE:
    *param_longp = data->info.httpproxycode;
    break;
  case CURLINFO_FILETIME:
    if(data->info.filetime > LONG_MAX)
      *param_longp = LONG_MAX;
    else if(data->info.filetime < LONG_MIN)
      *param_longp = LONG_MIN;
    else
      *param_longp = (long)data->info.filetime;
    break;
  case CURLINFO_HEADER_SIZE:
    *param_longp = (long)data->info.header_size;
    break;
  case CURLINFO_REQUEST_SIZE:
    *param_longp = (long)data->info.request_size;
    break;
  case CURLINFO_SSL_VERIFYRESULT:
    *param_longp = data->set.ssl.certverifyresult;
    break;
  case CURLINFO_PROXY_SSL_VERIFYRESULT:
    *param_longp = data->set.proxy_ssl.certverifyresult;
    break;
  case CURLINFO_REDIRECT_COUNT:
    *param_longp = data->set.followlocation;
    break;
  case CURLINFO_HTTPAUTH_AVAIL:
    lptr.to_long = param_longp;
    *lptr.to_ulong = data->info.httpauthavail;
    break;
  case CURLINFO_PROXYAUTH_AVAIL:
    lptr.to_long = param_longp;
    *lptr.to_ulong = data->info.proxyauthavail;
    break;
  case CURLINFO_OS_ERRNO:
    *param_longp = data->state.os_errno;
    break;
  case CURLINFO_NUM_CONNECTS:
    *param_longp = data->info.numconnects;
    break;
  case CURLINFO_LASTSOCKET:
    sockfd = Curl_getconnectinfo(data, NULL);

    /* note: this is not a good conversion for systems with 64 bit sockets and
       32 bit longs */
    if(sockfd != CURL_SOCKET_BAD)
      *param_longp = (long)sockfd;
    else
      /* this interface is documented to return -1 in case of badness, which
         may not be the same as the CURL_SOCKET_BAD value */
      *param_longp = -1;
    break;
  case CURLINFO_PRIMARY_PORT:
    /* Return the (remote) port of the most recent (primary) connection */
    *param_longp = data->info.conn_primary_port;
    break;
  case CURLINFO_LOCAL_PORT:
    /* Return the local port of the most recent (primary) connection */
    *param_longp = data->info.conn_local_port;
    break;
  case CURLINFO_CONDITION_UNMET:
    /* return if the condition prevented the document to get transferred */
    *param_longp = data->info.timecond ? 1L : 0L;
    break;
  case CURLINFO_RTSP_CLIENT_CSEQ:
    *param_longp = data->state.rtsp_next_client_CSeq;
    break;
  case CURLINFO_RTSP_SERVER_CSEQ:
    *param_longp = data->state.rtsp_next_server_CSeq;
    break;
  case CURLINFO_RTSP_CSEQ_RECV:
    *param_longp = data->state.rtsp_CSeq_recv;
    break;
  case CURLINFO_HTTP_VERSION:
    switch(data->info.httpversion) {
    case 10:
      *param_longp = CURL_HTTP_VERSION_1_0;
      break;
    case 11:
      *param_longp = CURL_HTTP_VERSION_1_1;
      break;
    case 20:
      *param_longp = CURL_HTTP_VERSION_2_0;
      break;
    case 30:
      *param_longp = CURL_HTTP_VERSION_3;
      break;
    default:
      *param_longp = CURL_HTTP_VERSION_NONE;
      break;
    }
    break;
  case CURLINFO_PROTOCOL:
    *param_longp = data->info.conn_protocol;
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}