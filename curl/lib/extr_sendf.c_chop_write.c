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
struct connectdata {TYPE_2__* handler; struct Curl_easy* data; } ;
struct TYPE_6__ {size_t (* fwrite_func ) (char*,int,size_t,scalar_t__) ;size_t (* fwrite_header ) (char*,int,size_t,scalar_t__) ;scalar_t__ writeheader; scalar_t__ out; } ;
struct TYPE_4__ {int keepon; } ;
struct Curl_easy {TYPE_3__ set; TYPE_1__ req; } ;
typedef  size_t (* curl_write_callback ) (char*,int,size_t,scalar_t__) ;
struct TYPE_5__ {int flags; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int CLIENTWRITE_BODY ; 
 int CLIENTWRITE_HEADER ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_WRITE_ERROR ; 
 size_t CURL_MAX_WRITE_SIZE ; 
 size_t CURL_WRITEFUNC_PAUSE ; 
 int /*<<< orphan*/  Curl_set_in_callback (struct Curl_easy*,int) ; 
 int KEEP_RECV_PAUSE ; 
 int PROTOPT_NONETWORK ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  pausewrite (struct Curl_easy*,int,char*,size_t) ; 

__attribute__((used)) static CURLcode chop_write(struct connectdata *conn,
                           int type,
                           char *optr,
                           size_t olen)
{
  struct Curl_easy *data = conn->data;
  curl_write_callback writeheader = NULL;
  curl_write_callback writebody = NULL;
  char *ptr = optr;
  size_t len = olen;

  if(!len)
    return CURLE_OK;

  /* If reading is paused, append this data to the already held data for this
     type. */
  if(data->req.keepon & KEEP_RECV_PAUSE)
    return pausewrite(data, type, ptr, len);

  /* Determine the callback(s) to use. */
  if(type & CLIENTWRITE_BODY)
    writebody = data->set.fwrite_func;
  if((type & CLIENTWRITE_HEADER) &&
     (data->set.fwrite_header || data->set.writeheader)) {
    /*
     * Write headers to the same callback or to the especially setup
     * header callback function (added after version 7.7.1).
     */
    writeheader =
      data->set.fwrite_header? data->set.fwrite_header: data->set.fwrite_func;
  }

  /* Chop data, write chunks. */
  while(len) {
    size_t chunklen = len <= CURL_MAX_WRITE_SIZE? len: CURL_MAX_WRITE_SIZE;

    if(writebody) {
      size_t wrote;
      Curl_set_in_callback(data, true);
      wrote = writebody(ptr, 1, chunklen, data->set.out);
      Curl_set_in_callback(data, false);

      if(CURL_WRITEFUNC_PAUSE == wrote) {
        if(conn->handler->flags & PROTOPT_NONETWORK) {
          /* Protocols that work without network cannot be paused. This is
             actually only FILE:// just now, and it can't pause since the
             transfer isn't done using the "normal" procedure. */
          failf(data, "Write callback asked for PAUSE when not supported!");
          return CURLE_WRITE_ERROR;
        }
        return pausewrite(data, type, ptr, len);
      }
      if(wrote != chunklen) {
        failf(data, "Failed writing body (%zu != %zu)", wrote, chunklen);
        return CURLE_WRITE_ERROR;
      }
    }

    ptr += chunklen;
    len -= chunklen;
  }

  if(writeheader) {
    size_t wrote;
    ptr = optr;
    len = olen;
    Curl_set_in_callback(data, true);
    wrote = writeheader(ptr, 1, len, data->set.writeheader);
    Curl_set_in_callback(data, false);

    if(CURL_WRITEFUNC_PAUSE == wrote)
      /* here we pass in the HEADER bit only since if this was body as well
         then it was passed already and clearly that didn't trigger the
         pause, so this is saved for later with the HEADER bit only */
      return pausewrite(data, CLIENTWRITE_HEADER, ptr, len);

    if(wrote != len) {
      failf(data, "Failed writing header");
      return CURLE_WRITE_ERROR;
    }
  }

  return CURLE_OK;
}