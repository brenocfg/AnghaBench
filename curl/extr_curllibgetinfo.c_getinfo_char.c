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
struct TYPE_8__ {char* contenttype; char* wouldredirect; char* conn_primary_ip; char* conn_local_ip; char* conn_scheme; } ;
struct TYPE_7__ {char** str; scalar_t__ private_data; } ;
struct TYPE_6__ {char* most_recent_ftp_entrypath; } ;
struct TYPE_5__ {char* url; } ;
struct Curl_easy {TYPE_4__ info; TYPE_3__ set; TYPE_2__ state; TYPE_1__ change; } ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int CURLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNKNOWN_OPTION ; 
#define  CURLINFO_CONTENT_TYPE 136 
#define  CURLINFO_EFFECTIVE_URL 135 
#define  CURLINFO_FTP_ENTRY_PATH 134 
#define  CURLINFO_LOCAL_IP 133 
#define  CURLINFO_PRIMARY_IP 132 
#define  CURLINFO_PRIVATE 131 
#define  CURLINFO_REDIRECT_URL 130 
#define  CURLINFO_RTSP_SESSION_ID 129 
#define  CURLINFO_SCHEME 128 
 size_t STRING_RTSP_SESSION_ID ; 

__attribute__((used)) static CURLcode getinfo_char(struct Curl_easy *data, CURLINFO info,
                             const char **param_charp)
{
  switch(info) {
  case CURLINFO_EFFECTIVE_URL:
    *param_charp = data->change.url?data->change.url:(char *)"";
    break;
  case CURLINFO_CONTENT_TYPE:
    *param_charp = data->info.contenttype;
    break;
  case CURLINFO_PRIVATE:
    *param_charp = (char *) data->set.private_data;
    break;
  case CURLINFO_FTP_ENTRY_PATH:
    /* Return the entrypath string from the most recent connection.
       This pointer was copied from the connectdata structure by FTP.
       The actual string may be free()ed by subsequent libcurl calls so
       it must be copied to a safer area before the next libcurl call.
       Callers must never free it themselves. */
    *param_charp = data->state.most_recent_ftp_entrypath;
    break;
  case CURLINFO_REDIRECT_URL:
    /* Return the URL this request would have been redirected to if that
       option had been enabled! */
    *param_charp = data->info.wouldredirect;
    break;
  case CURLINFO_PRIMARY_IP:
    /* Return the ip address of the most recent (primary) connection */
    *param_charp = data->info.conn_primary_ip;
    break;
  case CURLINFO_LOCAL_IP:
    /* Return the source/local ip address of the most recent (primary)
       connection */
    *param_charp = data->info.conn_local_ip;
    break;
  case CURLINFO_RTSP_SESSION_ID:
    *param_charp = data->set.str[STRING_RTSP_SESSION_ID];
    break;
  case CURLINFO_SCHEME:
    *param_charp = data->info.conn_scheme;
    break;

  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}