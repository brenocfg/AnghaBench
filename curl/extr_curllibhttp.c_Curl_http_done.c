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
struct TYPE_10__ {int /*<<< orphan*/  retry; } ;
struct connectdata {TYPE_4__ bits; int /*<<< orphan*/  seek_client; int /*<<< orphan*/  seek_func; struct Curl_easy* data; } ;
struct HTTP {int /*<<< orphan*/  form; scalar_t__ send_buffer; } ;
struct TYPE_12__ {scalar_t__ bytecount; scalar_t__ headerbytecount; scalar_t__ deductheadercount; struct HTTP* protop; } ;
struct TYPE_11__ {int /*<<< orphan*/  connect_only; int /*<<< orphan*/  seek_client; int /*<<< orphan*/  seek_func; } ;
struct TYPE_8__ {void* multipass; } ;
struct TYPE_7__ {void* multipass; } ;
struct TYPE_9__ {TYPE_2__ authproxy; TYPE_1__ authhost; } ;
struct Curl_easy {TYPE_6__ req; TYPE_5__ set; TYPE_3__ state; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_GOT_NOTHING ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_add_buffer_free (scalar_t__*) ; 
 int /*<<< orphan*/  Curl_http2_done (struct connectdata*,int) ; 
 int /*<<< orphan*/  Curl_mime_cleanpart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Curl_unencode_cleanup (struct connectdata*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 

CURLcode Curl_http_done(struct connectdata *conn,
                        CURLcode status, bool premature)
{
  struct Curl_easy *data = conn->data;
  struct HTTP *http = data->req.protop;

  /* Clear multipass flag. If authentication isn't done yet, then it will get
   * a chance to be set back to true when we output the next auth header */
  data->state.authhost.multipass = FALSE;
  data->state.authproxy.multipass = FALSE;

  Curl_unencode_cleanup(conn);

  /* set the proper values (possibly modified on POST) */
  conn->seek_func = data->set.seek_func; /* restore */
  conn->seek_client = data->set.seek_client; /* restore */

  if(!http)
    return CURLE_OK;

  if(http->send_buffer) {
    Curl_add_buffer_free(&http->send_buffer);
  }

  Curl_http2_done(conn, premature);

  Curl_mime_cleanpart(&http->form);

  if(status)
    return status;

  if(!premature && /* this check is pointless when DONE is called before the
                      entire operation is complete */
     !conn->bits.retry &&
     !data->set.connect_only &&
     (data->req.bytecount +
      data->req.headerbytecount -
      data->req.deductheadercount) <= 0) {
    /* If this connection isn't simply closed to be retried, AND nothing was
       read from the HTTP server (that counts), this can't be right so we
       return an error here */
    failf(data, "Empty reply from server");
    return CURLE_GOT_NOTHING;
  }

  return CURLE_OK;
}