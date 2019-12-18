#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct connectdata {int /*<<< orphan*/ * sock; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_SEND_ERROR ; 
 unsigned char CURL_IAC ; 
 int Curl_poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  Curl_write (struct connectdata*,int /*<<< orphan*/ ,unsigned char*,size_t,size_t*) ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (size_t) ; 

__attribute__((used)) static CURLcode send_telnet_data(struct connectdata *conn,
                                 char *buffer, ssize_t nread)
{
  ssize_t escapes, i, outlen;
  unsigned char *outbuf = NULL;
  CURLcode result = CURLE_OK;
  ssize_t bytes_written, total_written;

  /* Determine size of new buffer after escaping */
  escapes = 0;
  for(i = 0; i < nread; i++)
    if((unsigned char)buffer[i] == CURL_IAC)
      escapes++;
  outlen = nread + escapes;

  if(outlen == nread)
    outbuf = (unsigned char *)buffer;
  else {
    ssize_t j;
    outbuf = malloc(nread + escapes + 1);
    if(!outbuf)
      return CURLE_OUT_OF_MEMORY;

    j = 0;
    for(i = 0; i < nread; i++) {
      outbuf[j++] = buffer[i];
      if((unsigned char)buffer[i] == CURL_IAC)
        outbuf[j++] = CURL_IAC;
    }
    outbuf[j] = '\0';
  }

  total_written = 0;
  while(!result && total_written < outlen) {
    /* Make sure socket is writable to avoid EWOULDBLOCK condition */
    struct pollfd pfd[1];
    pfd[0].fd = conn->sock[FIRSTSOCKET];
    pfd[0].events = POLLOUT;
    switch(Curl_poll(pfd, 1, -1)) {
      case -1:                    /* error, abort writing */
      case 0:                     /* timeout (will never happen) */
        result = CURLE_SEND_ERROR;
        break;
      default:                    /* write! */
        bytes_written = 0;
        result = Curl_write(conn, conn->sock[FIRSTSOCKET],
                            outbuf + total_written,
                            outlen - total_written,
                            &bytes_written);
        total_written += bytes_written;
        break;
    }
  }

  /* Free malloc copy if escaped */
  if(outbuf != (unsigned char *)buffer)
    free(outbuf);

  return result;
}