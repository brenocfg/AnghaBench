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
struct pingpong {size_t nread_resp; char* linestart_resp; char* cache; int cache_size; void* pending_resp; scalar_t__ (* endofresp ) (struct connectdata*,char*,int,int*) ;struct connectdata* conn; } ;
struct connectdata {int data_prot; int /*<<< orphan*/  sec_complete; struct Curl_easy* data; } ;
struct TYPE_6__ {int buffer_size; scalar_t__ verbose; } ;
struct TYPE_5__ {long headerbytecount; } ;
struct TYPE_4__ {char* buffer; } ;
struct Curl_easy {TYPE_3__ set; TYPE_2__ req; TYPE_1__ state; } ;
typedef  int ssize_t ;
typedef  enum protection_level { ____Placeholder_protection_level } protection_level ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_HEADER ; 
 scalar_t__ CURLE_AGAIN ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_RECV_ERROR ; 
 int /*<<< orphan*/  CURLINFO_HEADER_IN ; 
 scalar_t__ Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ Curl_convert_from_network (struct Curl_easy*,char*,int) ; 
 int /*<<< orphan*/  Curl_debug (struct Curl_easy*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ Curl_read (struct connectdata*,int /*<<< orphan*/ ,char*,size_t,int*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int PROT_CLEAR ; 
 int PROT_LAST ; 
 int PROT_NONE ; 
 int TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char* const,char*,size_t) ; 
 scalar_t__ stub1 (struct connectdata*,char*,int,int*) ; 

CURLcode Curl_pp_readresp(curl_socket_t sockfd,
                          struct pingpong *pp,
                          int *code, /* return the server code if done */
                          size_t *size) /* size of the response */
{
  ssize_t perline; /* count bytes per line */
  bool keepon = TRUE;
  ssize_t gotbytes;
  char *ptr;
  struct connectdata *conn = pp->conn;
  struct Curl_easy *data = conn->data;
  char * const buf = data->state.buffer;
  CURLcode result = CURLE_OK;

  *code = 0; /* 0 for errors or not done */
  *size = 0;

  ptr = buf + pp->nread_resp;

  /* number of bytes in the current line, so far */
  perline = (ssize_t)(ptr-pp->linestart_resp);

  while((pp->nread_resp < (size_t)data->set.buffer_size) &&
        (keepon && !result)) {

    if(pp->cache) {
      /* we had data in the "cache", copy that instead of doing an actual
       * read
       *
       * pp->cache_size is cast to ssize_t here.  This should be safe, because
       * it would have been populated with something of size int to begin
       * with, even though its datatype may be larger than an int.
       */
      if((ptr + pp->cache_size) > (buf + data->set.buffer_size + 1)) {
        failf(data, "cached response data too big to handle");
        return CURLE_RECV_ERROR;
      }
      memcpy(ptr, pp->cache, pp->cache_size);
      gotbytes = (ssize_t)pp->cache_size;
      free(pp->cache);    /* free the cache */
      pp->cache = NULL;   /* clear the pointer */
      pp->cache_size = 0; /* zero the size just in case */
    }
    else {
#ifdef HAVE_GSSAPI
      enum protection_level prot = conn->data_prot;
      conn->data_prot = PROT_CLEAR;
#endif
      DEBUGASSERT((ptr + data->set.buffer_size - pp->nread_resp) <=
                  (buf + data->set.buffer_size + 1));
      result = Curl_read(conn, sockfd, ptr,
                         data->set.buffer_size - pp->nread_resp,
                         &gotbytes);
#ifdef HAVE_GSSAPI
      DEBUGASSERT(prot  > PROT_NONE && prot < PROT_LAST);
      conn->data_prot = prot;
#endif
      if(result == CURLE_AGAIN)
        return CURLE_OK; /* return */

      if(!result && (gotbytes > 0))
        /* convert from the network encoding */
        result = Curl_convert_from_network(data, ptr, gotbytes);
      /* Curl_convert_from_network calls failf if unsuccessful */

      if(result)
        /* Set outer result variable to this error. */
        keepon = FALSE;
    }

    if(!keepon)
      ;
    else if(gotbytes <= 0) {
      keepon = FALSE;
      result = CURLE_RECV_ERROR;
      failf(data, "response reading failed");
    }
    else {
      /* we got a whole chunk of data, which can be anything from one
       * byte to a set of lines and possible just a piece of the last
       * line */
      ssize_t i;
      ssize_t clipamount = 0;
      bool restart = FALSE;

      data->req.headerbytecount += (long)gotbytes;

      pp->nread_resp += gotbytes;
      for(i = 0; i < gotbytes; ptr++, i++) {
        perline++;
        if(*ptr == '\n') {
          /* a newline is CRLF in pp-talk, so the CR is ignored as
             the line isn't really terminated until the LF comes */

          /* output debug output if that is requested */
#ifdef HAVE_GSSAPI
          if(!conn->sec_complete)
#endif
            if(data->set.verbose)
              Curl_debug(data, CURLINFO_HEADER_IN,
                         pp->linestart_resp, (size_t)perline);

          /*
           * We pass all response-lines to the callback function registered
           * for "headers". The response lines can be seen as a kind of
           * headers.
           */
          result = Curl_client_write(conn, CLIENTWRITE_HEADER,
                                     pp->linestart_resp, perline);
          if(result)
            return result;

          if(pp->endofresp(conn, pp->linestart_resp, perline, code)) {
            /* This is the end of the last line, copy the last line to the
               start of the buffer and zero terminate, for old times sake */
            size_t n = ptr - pp->linestart_resp;
            memmove(buf, pp->linestart_resp, n);
            buf[n] = 0; /* zero terminate */
            keepon = FALSE;
            pp->linestart_resp = ptr + 1; /* advance pointer */
            i++; /* skip this before getting out */

            *size = pp->nread_resp; /* size of the response */
            pp->nread_resp = 0; /* restart */
            break;
          }
          perline = 0; /* line starts over here */
          pp->linestart_resp = ptr + 1;
        }
      }

      if(!keepon && (i != gotbytes)) {
        /* We found the end of the response lines, but we didn't parse the
           full chunk of data we have read from the server. We therefore need
           to store the rest of the data to be checked on the next invoke as
           it may actually contain another end of response already! */
        clipamount = gotbytes - i;
        restart = TRUE;
        DEBUGF(infof(data, "Curl_pp_readresp_ %d bytes of trailing "
                     "server response left\n",
                     (int)clipamount));
      }
      else if(keepon) {

        if((perline == gotbytes) && (gotbytes > data->set.buffer_size/2)) {
          /* We got an excessive line without newlines and we need to deal
             with it. We keep the first bytes of the line then we throw
             away the rest. */
          infof(data, "Excessive server response line length received, "
                "%zd bytes. Stripping\n", gotbytes);
          restart = TRUE;

          /* we keep 40 bytes since all our pingpong protocols are only
             interested in the first piece */
          clipamount = 40;
        }
        else if(pp->nread_resp > (size_t)data->set.buffer_size/2) {
          /* We got a large chunk of data and there's potentially still
             trailing data to take care of, so we put any such part in the
             "cache", clear the buffer to make space and restart. */
          clipamount = perline;
          restart = TRUE;
        }
      }
      else if(i == gotbytes)
        restart = TRUE;

      if(clipamount) {
        pp->cache_size = clipamount;
        pp->cache = malloc(pp->cache_size);
        if(pp->cache)
          memcpy(pp->cache, pp->linestart_resp, pp->cache_size);
        else
          return CURLE_OUT_OF_MEMORY;
      }
      if(restart) {
        /* now reset a few variables to start over nicely from the start of
           the big buffer */
        pp->nread_resp = 0; /* start over from scratch in the buffer */
        ptr = pp->linestart_resp = buf;
        perline = 0;
      }

    } /* there was data */

  } /* while there's buffer left and loop is requested */

  pp->pending_resp = FALSE;

  return result;
}