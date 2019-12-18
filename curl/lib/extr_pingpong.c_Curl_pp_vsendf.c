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
typedef  int /*<<< orphan*/  va_list ;
struct pingpong {scalar_t__ sendleft; size_t sendsize; char* sendthis; int /*<<< orphan*/  response; struct connectdata* conn; } ;
struct connectdata {int data_prot; struct Curl_easy* data; int /*<<< orphan*/ * sock; } ;
struct TYPE_2__ {scalar_t__ verbose; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  scalar_t__ ssize_t ;
typedef  enum protection_level { ____Placeholder_protection_level } protection_level ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_OUT_OF_MEMORY ; 
 scalar_t__ CURLE_SEND_ERROR ; 
 int /*<<< orphan*/  CURLINFO_HEADER_OUT ; 
 scalar_t__ Curl_convert_to_network (struct Curl_easy*,char*,size_t) ; 
 int /*<<< orphan*/  Curl_debug (struct Curl_easy*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  Curl_now () ; 
 int /*<<< orphan*/  Curl_pp_init (struct pingpong*) ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,char*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 size_t FIRSTSOCKET ; 
 int PROT_CMD ; 
 int PROT_LAST ; 
 int PROT_NONE ; 
 char* aprintf (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t strlen (char*) ; 
 char* vaprintf (char*,int /*<<< orphan*/ ) ; 

CURLcode Curl_pp_vsendf(struct pingpong *pp,
                        const char *fmt,
                        va_list args)
{
  ssize_t bytes_written;
  size_t write_len;
  char *fmt_crlf;
  char *s;
  CURLcode result;
  struct connectdata *conn = pp->conn;
  struct Curl_easy *data;

#ifdef HAVE_GSSAPI
  enum protection_level data_sec;
#endif

  DEBUGASSERT(pp->sendleft == 0);
  DEBUGASSERT(pp->sendsize == 0);
  DEBUGASSERT(pp->sendthis == NULL);

  if(!conn)
    /* can't send without a connection! */
    return CURLE_SEND_ERROR;

  data = conn->data;

  fmt_crlf = aprintf("%s\r\n", fmt); /* append a trailing CRLF */
  if(!fmt_crlf)
    return CURLE_OUT_OF_MEMORY;

  s = vaprintf(fmt_crlf, args); /* trailing CRLF appended */
  free(fmt_crlf);
  if(!s)
    return CURLE_OUT_OF_MEMORY;

  bytes_written = 0;
  write_len = strlen(s);

  Curl_pp_init(pp);

  result = Curl_convert_to_network(data, s, write_len);
  /* Curl_convert_to_network calls failf if unsuccessful */
  if(result) {
    free(s);
    return result;
  }

#ifdef HAVE_GSSAPI
  conn->data_prot = PROT_CMD;
#endif
  result = Curl_write(conn, conn->sock[FIRSTSOCKET], s, write_len,
                     &bytes_written);
#ifdef HAVE_GSSAPI
  data_sec = conn->data_prot;
  DEBUGASSERT(data_sec > PROT_NONE && data_sec < PROT_LAST);
  conn->data_prot = data_sec;
#endif

  if(result) {
    free(s);
    return result;
  }

  if(conn->data->set.verbose)
    Curl_debug(conn->data, CURLINFO_HEADER_OUT, s, (size_t)bytes_written);

  if(bytes_written != (ssize_t)write_len) {
    /* the whole chunk was not sent, keep it around and adjust sizes */
    pp->sendthis = s;
    pp->sendsize = write_len;
    pp->sendleft = write_len - bytes_written;
  }
  else {
    free(s);
    pp->sendthis = NULL;
    pp->sendleft = pp->sendsize = 0;
    pp->response = Curl_now();
  }

  return CURLE_OK;
}