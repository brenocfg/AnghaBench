#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ proxytype; } ;
struct connectdata {int httpversion; TYPE_2__ http_proxy; TYPE_1__* handler; int /*<<< orphan*/ * sock; struct Curl_easy* data; } ;
struct TYPE_14__ {char* postdata; long postsize; void* fread_in; scalar_t__ fread_func; } ;
struct HTTP {char* postdata; long postsize; int /*<<< orphan*/  sending; TYPE_7__* send_buffer; TYPE_5__ backup; } ;
struct TYPE_15__ {char* ulbuf; void* in; scalar_t__ fread_func; } ;
struct TYPE_13__ {size_t writebytecount; struct HTTP* protop; } ;
struct TYPE_12__ {scalar_t__ verbose; } ;
struct Curl_easy {TYPE_6__ state; TYPE_4__ req; TYPE_3__ set; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ curl_read_callback ;
typedef  long curl_off_t ;
struct TYPE_16__ {char* buffer; size_t size_used; } ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_7__ Curl_send_buffer ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_SEND_ERROR ; 
 int /*<<< orphan*/  CURLINFO_DATA_OUT ; 
 int /*<<< orphan*/  CURLINFO_HEADER_OUT ; 
 size_t CURLMIN (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ CURLPROXY_HTTPS ; 
 int /*<<< orphan*/  CURL_MAX_WRITE_SIZE ; 
 int /*<<< orphan*/  Curl_add_buffer_free (TYPE_7__**) ; 
 scalar_t__ Curl_convert_to_network (struct Curl_easy*,char*,size_t) ; 
 int /*<<< orphan*/  Curl_debug (struct Curl_easy*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ Curl_get_upload_buffer (struct Curl_easy*) ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadCounter (struct Curl_easy*,size_t) ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  HTTPSEND_BODY ; 
 int /*<<< orphan*/  HTTPSEND_REQUEST ; 
 int PROTOPT_SSL ; 
 int SECONDARYSOCKET ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ readmoredata ; 

CURLcode Curl_add_buffer_send(Curl_send_buffer **inp,
                              struct connectdata *conn,

                              /* add the number of sent bytes to this
                                 counter */
                              curl_off_t *bytes_written,

                              /* how much of the buffer contains body data */
                              size_t included_body_bytes,
                              int socketindex)
{
  ssize_t amount;
  CURLcode result;
  char *ptr;
  size_t size;
  struct Curl_easy *data = conn->data;
  struct HTTP *http = data->req.protop;
  size_t sendsize;
  curl_socket_t sockfd;
  size_t headersize;
  Curl_send_buffer *in = *inp;

  DEBUGASSERT(socketindex <= SECONDARYSOCKET);

  sockfd = conn->sock[socketindex];

  /* The looping below is required since we use non-blocking sockets, but due
     to the circumstances we will just loop and try again and again etc */

  ptr = in->buffer;
  size = in->size_used;

  headersize = size - included_body_bytes; /* the initial part that isn't body
                                              is header */

  DEBUGASSERT(size > included_body_bytes);

  result = Curl_convert_to_network(data, ptr, headersize);
  /* Curl_convert_to_network calls failf if unsuccessful */
  if(result) {
    /* conversion failed, free memory and return to the caller */
    Curl_add_buffer_free(inp);
    return result;
  }

  if((conn->handler->flags & PROTOPT_SSL ||
     conn->http_proxy.proxytype == CURLPROXY_HTTPS)
     && conn->httpversion != 20) {
    /* We never send more than CURL_MAX_WRITE_SIZE bytes in one single chunk
       when we speak HTTPS, as if only a fraction of it is sent now, this data
       needs to fit into the normal read-callback buffer later on and that
       buffer is using this size.
    */

    sendsize = CURLMIN(size, CURL_MAX_WRITE_SIZE);

    /* OpenSSL is very picky and we must send the SAME buffer pointer to the
       library when we attempt to re-send this buffer. Sending the same data
       is not enough, we must use the exact same address. For this reason, we
       must copy the data to the uploadbuffer first, since that is the buffer
       we will be using if this send is retried later.
    */
    result = Curl_get_upload_buffer(data);
    if(result) {
      /* malloc failed, free memory and return to the caller */
      Curl_add_buffer_free(&in);
      return result;
    }
    memcpy(data->state.ulbuf, ptr, sendsize);
    ptr = data->state.ulbuf;
  }
  else
    sendsize = size;

  result = Curl_write(conn, sockfd, ptr, sendsize, &amount);

  if(!result) {
    /*
     * Note that we may not send the entire chunk at once, and we have a set
     * number of data bytes at the end of the big buffer (out of which we may
     * only send away a part).
     */
    /* how much of the header that was sent */
    size_t headlen = (size_t)amount>headersize ? headersize : (size_t)amount;
    size_t bodylen = amount - headlen;

    if(data->set.verbose) {
      /* this data _may_ contain binary stuff */
      Curl_debug(data, CURLINFO_HEADER_OUT, ptr, headlen);
      if(bodylen) {
        /* there was body data sent beyond the initial header part, pass that
           on to the debug callback too */
        Curl_debug(data, CURLINFO_DATA_OUT,
                   ptr + headlen, bodylen);
      }
    }

    /* 'amount' can never be a very large value here so typecasting it so a
       signed 31 bit value should not cause problems even if ssize_t is
       64bit */
    *bytes_written += (long)amount;

    if(http) {
      /* if we sent a piece of the body here, up the byte counter for it
         accordingly */
      data->req.writebytecount += bodylen;
      Curl_pgrsSetUploadCounter(data, data->req.writebytecount);

      if((size_t)amount != size) {
        /* The whole request could not be sent in one system call. We must
           queue it up and send it later when we get the chance. We must not
           loop here and wait until it might work again. */

        size -= amount;

        ptr = in->buffer + amount;

        /* backup the currently set pointers */
        http->backup.fread_func = data->state.fread_func;
        http->backup.fread_in = data->state.in;
        http->backup.postdata = http->postdata;
        http->backup.postsize = http->postsize;

        /* set the new pointers for the request-sending */
        data->state.fread_func = (curl_read_callback)readmoredata;
        data->state.in = (void *)conn;
        http->postdata = ptr;
        http->postsize = (curl_off_t)size;

        http->send_buffer = in;
        http->sending = HTTPSEND_REQUEST;

        return CURLE_OK;
      }
      http->sending = HTTPSEND_BODY;
      /* the full buffer was sent, clean up and return */
    }
    else {
      if((size_t)amount != size)
        /* We have no continue-send mechanism now, fail. This can only happen
           when this function is used from the CONNECT sending function. We
           currently (stupidly) assume that the whole request is always sent
           away in the first single chunk.

           This needs FIXing.
        */
        return CURLE_SEND_ERROR;
    }
  }
  Curl_add_buffer_free(&in);

  return result;
}