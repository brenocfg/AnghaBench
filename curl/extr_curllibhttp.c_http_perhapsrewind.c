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
struct TYPE_7__ {int /*<<< orphan*/  rewindaftersend; int /*<<< orphan*/  protoconnstart; scalar_t__ authneg; } ;
struct connectdata {TYPE_3__ bits; struct Curl_easy* data; } ;
struct HTTP {int postsize; } ;
struct TYPE_8__ {int writebytecount; scalar_t__ size; struct HTTP* protop; } ;
struct TYPE_6__ {int infilesize; } ;
struct TYPE_5__ {int httpreq; } ;
struct Curl_easy {TYPE_4__ req; TYPE_2__ state; TYPE_1__ set; } ;
typedef  int curl_off_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_readrewind (struct connectdata*) ; 
 int /*<<< orphan*/  FALSE ; 
#define  HTTPREQ_GET 133 
#define  HTTPREQ_HEAD 132 
#define  HTTPREQ_POST 131 
#define  HTTPREQ_POST_FORM 130 
#define  HTTPREQ_POST_MIME 129 
#define  HTTPREQ_PUT 128 
 int /*<<< orphan*/  streamclose (struct connectdata*,char*) ; 

__attribute__((used)) static CURLcode http_perhapsrewind(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  struct HTTP *http = data->req.protop;
  curl_off_t bytessent;
  curl_off_t expectsend = -1; /* default is unknown */

  if(!http)
    /* If this is still NULL, we have not reach very far and we can safely
       skip this rewinding stuff */
    return CURLE_OK;

  switch(data->set.httpreq) {
  case HTTPREQ_GET:
  case HTTPREQ_HEAD:
    return CURLE_OK;
  default:
    break;
  }

  bytessent = data->req.writebytecount;

  if(conn->bits.authneg) {
    /* This is a state where we are known to be negotiating and we don't send
       any data then. */
    expectsend = 0;
  }
  else if(!conn->bits.protoconnstart) {
    /* HTTP CONNECT in progress: there is no body */
    expectsend = 0;
  }
  else {
    /* figure out how much data we are expected to send */
    switch(data->set.httpreq) {
    case HTTPREQ_POST:
      if(data->state.infilesize != -1)
        expectsend = data->state.infilesize;
      break;
    case HTTPREQ_PUT:
      if(data->state.infilesize != -1)
        expectsend = data->state.infilesize;
      break;
    case HTTPREQ_POST_FORM:
    case HTTPREQ_POST_MIME:
      expectsend = http->postsize;
      break;
    default:
      break;
    }
  }

  conn->bits.rewindaftersend = FALSE; /* default */

  if((expectsend == -1) || (expectsend > bytessent)) {
#if defined(USE_NTLM)
    /* There is still data left to send */
    if((data->state.authproxy.picked == CURLAUTH_NTLM) ||
       (data->state.authhost.picked == CURLAUTH_NTLM) ||
       (data->state.authproxy.picked == CURLAUTH_NTLM_WB) ||
       (data->state.authhost.picked == CURLAUTH_NTLM_WB)) {
      if(((expectsend - bytessent) < 2000) ||
         (conn->ntlm.state != NTLMSTATE_NONE) ||
         (conn->proxyntlm.state != NTLMSTATE_NONE)) {
        /* The NTLM-negotiation has started *OR* there is just a little (<2K)
           data left to send, keep on sending. */

        /* rewind data when completely done sending! */
        if(!conn->bits.authneg && (conn->writesockfd != CURL_SOCKET_BAD)) {
          conn->bits.rewindaftersend = TRUE;
          infof(data, "Rewind stream after send\n");
        }

        return CURLE_OK;
      }

      if(conn->bits.close)
        /* this is already marked to get closed */
        return CURLE_OK;

      infof(data, "NTLM send, close instead of sending %"
            CURL_FORMAT_CURL_OFF_T " bytes\n",
            (curl_off_t)(expectsend - bytessent));
    }
#endif
#if defined(USE_SPNEGO)
    /* There is still data left to send */
    if((data->state.authproxy.picked == CURLAUTH_NEGOTIATE) ||
       (data->state.authhost.picked == CURLAUTH_NEGOTIATE)) {
      if(((expectsend - bytessent) < 2000) ||
         (conn->negotiate.state != GSS_AUTHNONE) ||
         (conn->proxyneg.state != GSS_AUTHNONE)) {
        /* The NEGOTIATE-negotiation has started *OR*
        there is just a little (<2K) data left to send, keep on sending. */

        /* rewind data when completely done sending! */
        if(!conn->bits.authneg && (conn->writesockfd != CURL_SOCKET_BAD)) {
          conn->bits.rewindaftersend = TRUE;
          infof(data, "Rewind stream after send\n");
        }

        return CURLE_OK;
      }

      if(conn->bits.close)
        /* this is already marked to get closed */
        return CURLE_OK;

      infof(data, "NEGOTIATE send, close instead of sending %"
        CURL_FORMAT_CURL_OFF_T " bytes\n",
        (curl_off_t)(expectsend - bytessent));
    }
#endif

    /* This is not NEGOTIATE/NTLM or many bytes left to send: close */
    streamclose(conn, "Mid-auth HTTP and much data left to send");
    data->req.size = 0; /* don't download any more than 0 bytes */

    /* There still is data left to send, but this connection is marked for
       closure so we can safely do the rewind right now */
  }

  if(bytessent)
    /* we rewind now at once since if we already sent something */
    return Curl_readrewind(conn);

  return CURLE_OK;
}