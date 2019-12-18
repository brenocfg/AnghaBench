#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Curl_chunker {int state; size_t hexindex; char* hexbuffer; size_t datasize; void* dataleft; } ;
struct connectdata {size_t trlPos; int* trailer; int trlMax; struct Curl_easy* data; struct Curl_chunker chunk; } ;
struct SingleRequest {int /*<<< orphan*/  writer_stack; int /*<<< orphan*/  ignorebody; } ;
struct TYPE_2__ {scalar_t__ http_te_skip; int /*<<< orphan*/  http_ce_skip; } ;
struct Curl_easy {TYPE_1__ set; struct SingleRequest req; } ;
typedef  size_t ssize_t ;
typedef  size_t curl_off_t ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CHUNKcode ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNKE_BAD_CHUNK ; 
 int /*<<< orphan*/  CHUNKE_ILLEGAL_HEX ; 
 int /*<<< orphan*/  CHUNKE_OK ; 
 int /*<<< orphan*/  CHUNKE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CHUNKE_PASSTHRU_ERROR ; 
 int /*<<< orphan*/  CHUNKE_STOP ; 
 int /*<<< orphan*/  CHUNKE_TOO_LONG_HEX ; 
#define  CHUNK_DATA 135 
#define  CHUNK_HEX 134 
#define  CHUNK_LF 133 
#define  CHUNK_POSTLF 132 
#define  CHUNK_STOP 131 
#define  CHUNK_TRAILER 130 
#define  CHUNK_TRAILER_CR 129 
#define  CHUNK_TRAILER_POSTCR 128 
 int /*<<< orphan*/  CLIENTWRITE_BODY ; 
 int /*<<< orphan*/  CLIENTWRITE_HEADER ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ Curl_convert_from_network (struct Curl_easy*,int*,size_t) ; 
 int /*<<< orphan*/  Curl_httpchunk_init (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_isxdigit_ascii (char) ; 
 scalar_t__ Curl_unencode_write (struct connectdata*,int /*<<< orphan*/ ,char*,size_t) ; 
 size_t MAXNUM_SIZE ; 
 void* curlx_sotouz (size_t) ; 
 int /*<<< orphan*/  curlx_strtoofft (int*,char**,int,size_t*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 char* realloc (char*,int /*<<< orphan*/ ) ; 

CHUNKcode Curl_httpchunk_read(struct connectdata *conn,
                              char *datap,
                              ssize_t datalen,
                              ssize_t *wrotep,
                              CURLcode *extrap)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct Curl_chunker *ch = &conn->chunk;
  struct SingleRequest *k = &data->req;
  size_t piece;
  curl_off_t length = (curl_off_t)datalen;
  size_t *wrote = (size_t *)wrotep;

  *wrote = 0; /* nothing's written yet */

  /* the original data is written to the client, but we go on with the
     chunk read process, to properly calculate the content length*/
  if(data->set.http_te_skip && !k->ignorebody) {
    result = Curl_client_write(conn, CLIENTWRITE_BODY, datap, datalen);
    if(result) {
      *extrap = result;
      return CHUNKE_PASSTHRU_ERROR;
    }
  }

  while(length) {
    switch(ch->state) {
    case CHUNK_HEX:
      if(Curl_isxdigit_ascii(*datap)) {
        if(ch->hexindex < MAXNUM_SIZE) {
          ch->hexbuffer[ch->hexindex] = *datap;
          datap++;
          length--;
          ch->hexindex++;
        }
        else {
          return CHUNKE_TOO_LONG_HEX; /* longer hex than we support */
        }
      }
      else {
        char *endptr;
        if(0 == ch->hexindex)
          /* This is illegal data, we received junk where we expected
             a hexadecimal digit. */
          return CHUNKE_ILLEGAL_HEX;

        /* length and datap are unmodified */
        ch->hexbuffer[ch->hexindex] = 0;

        /* convert to host encoding before calling strtoul */
        result = Curl_convert_from_network(conn->data, ch->hexbuffer,
                                           ch->hexindex);
        if(result) {
          /* Curl_convert_from_network calls failf if unsuccessful */
          /* Treat it as a bad hex character */
          return CHUNKE_ILLEGAL_HEX;
        }

        if(curlx_strtoofft(ch->hexbuffer, &endptr, 16, &ch->datasize))
          return CHUNKE_ILLEGAL_HEX;
        ch->state = CHUNK_LF; /* now wait for the CRLF */
      }
      break;

    case CHUNK_LF:
      /* waiting for the LF after a chunk size */
      if(*datap == 0x0a) {
        /* we're now expecting data to come, unless size was zero! */
        if(0 == ch->datasize) {
          ch->state = CHUNK_TRAILER; /* now check for trailers */
          conn->trlPos = 0;
        }
        else
          ch->state = CHUNK_DATA;
      }

      datap++;
      length--;
      break;

    case CHUNK_DATA:
      /* We expect 'datasize' of data. We have 'length' right now, it can be
         more or less than 'datasize'. Get the smallest piece.
      */
      piece = curlx_sotouz((ch->datasize >= length)?length:ch->datasize);

      /* Write the data portion available */
      if(!conn->data->set.http_te_skip && !k->ignorebody) {
        if(!conn->data->set.http_ce_skip && k->writer_stack)
          result = Curl_unencode_write(conn, k->writer_stack, datap, piece);
        else
          result = Curl_client_write(conn, CLIENTWRITE_BODY, datap, piece);

        if(result) {
          *extrap = result;
          return CHUNKE_PASSTHRU_ERROR;
        }
      }

      *wrote += piece;
      ch->datasize -= piece; /* decrease amount left to expect */
      datap += piece;    /* move read pointer forward */
      length -= piece;   /* decrease space left in this round */

      if(0 == ch->datasize)
        /* end of data this round, we now expect a trailing CRLF */
        ch->state = CHUNK_POSTLF;
      break;

    case CHUNK_POSTLF:
      if(*datap == 0x0a) {
        /* The last one before we go back to hex state and start all over. */
        Curl_httpchunk_init(conn); /* sets state back to CHUNK_HEX */
      }
      else if(*datap != 0x0d)
        return CHUNKE_BAD_CHUNK;
      datap++;
      length--;
      break;

    case CHUNK_TRAILER:
      if((*datap == 0x0d) || (*datap == 0x0a)) {
        /* this is the end of a trailer, but if the trailer was zero bytes
           there was no trailer and we move on */

        if(conn->trlPos) {
          /* we allocate trailer with 3 bytes extra room to fit this */
          conn->trailer[conn->trlPos++] = 0x0d;
          conn->trailer[conn->trlPos++] = 0x0a;
          conn->trailer[conn->trlPos] = 0;

          /* Convert to host encoding before calling Curl_client_write */
          result = Curl_convert_from_network(conn->data, conn->trailer,
                                             conn->trlPos);
          if(result)
            /* Curl_convert_from_network calls failf if unsuccessful */
            /* Treat it as a bad chunk */
            return CHUNKE_BAD_CHUNK;

          if(!data->set.http_te_skip) {
            result = Curl_client_write(conn, CLIENTWRITE_HEADER,
                                       conn->trailer, conn->trlPos);
            if(result) {
              *extrap = result;
              return CHUNKE_PASSTHRU_ERROR;
            }
          }
          conn->trlPos = 0;
          ch->state = CHUNK_TRAILER_CR;
          if(*datap == 0x0a)
            /* already on the LF */
            break;
        }
        else {
          /* no trailer, we're on the final CRLF pair */
          ch->state = CHUNK_TRAILER_POSTCR;
          break; /* don't advance the pointer */
        }
      }
      else {
        /* conn->trailer is assumed to be freed in url.c on a
           connection basis */
        if(conn->trlPos >= conn->trlMax) {
          /* we always allocate three extra bytes, just because when the full
             header has been received we append CRLF\0 */
          char *ptr;
          if(conn->trlMax) {
            conn->trlMax *= 2;
            ptr = realloc(conn->trailer, conn->trlMax + 3);
          }
          else {
            conn->trlMax = 128;
            ptr = malloc(conn->trlMax + 3);
          }
          if(!ptr)
            return CHUNKE_OUT_OF_MEMORY;
          conn->trailer = ptr;
        }
        conn->trailer[conn->trlPos++]=*datap;
      }
      datap++;
      length--;
      break;

    case CHUNK_TRAILER_CR:
      if(*datap == 0x0a) {
        ch->state = CHUNK_TRAILER_POSTCR;
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_TRAILER_POSTCR:
      /* We enter this state when a CR should arrive so we expect to
         have to first pass a CR before we wait for LF */
      if((*datap != 0x0d) && (*datap != 0x0a)) {
        /* not a CR then it must be another header in the trailer */
        ch->state = CHUNK_TRAILER;
        break;
      }
      if(*datap == 0x0d) {
        /* skip if CR */
        datap++;
        length--;
      }
      /* now wait for the final LF */
      ch->state = CHUNK_STOP;
      break;

    case CHUNK_STOP:
      if(*datap == 0x0a) {
        length--;

        /* Record the length of any data left in the end of the buffer
           even if there's no more chunks to read */
        ch->dataleft = curlx_sotouz(length);

        return CHUNKE_STOP; /* return stop */
      }
      else
        return CHUNKE_BAD_CHUNK;
    }
  }
  return CHUNKE_OK;
}