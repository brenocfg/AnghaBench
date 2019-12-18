#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int data_prot; TYPE_2__* data; int /*<<< orphan*/ * sock; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  s ;
typedef  enum protection_level { ____Placeholder_protection_level } protection_level ;
struct TYPE_4__ {scalar_t__ verbose; } ;
struct TYPE_5__ {TYPE_1__ set; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_BAD_FUNCTION_ARGUMENT ; 
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_HEADER_OUT ; 
 scalar_t__ Curl_convert_to_network (TYPE_2__*,char*,size_t) ; 
 int /*<<< orphan*/  Curl_debug (TYPE_2__*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,char*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 size_t FIRSTSOCKET ; 
 int PROT_CMD ; 
 int PROT_LAST ; 
 int PROT_NONE ; 
 int SBUF_SIZE ; 
 int /*<<< orphan*/  memcpy (char**,char const*,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

CURLcode Curl_ftpsend(struct connectdata *conn, const char *cmd)
{
  ssize_t bytes_written;
#define SBUF_SIZE 1024
  char s[SBUF_SIZE];
  size_t write_len;
  char *sptr = s;
  CURLcode result = CURLE_OK;
#ifdef HAVE_GSSAPI
  enum protection_level data_sec = conn->data_prot;
#endif

  if(!cmd)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  write_len = strlen(cmd);
  if(!write_len || write_len > (sizeof(s) -3))
    return CURLE_BAD_FUNCTION_ARGUMENT;

  memcpy(&s, cmd, write_len);
  strcpy(&s[write_len], "\r\n"); /* append a trailing CRLF */
  write_len += 2;
  bytes_written = 0;

  result = Curl_convert_to_network(conn->data, s, write_len);
  /* Curl_convert_to_network calls failf if unsuccessful */
  if(result)
    return result;

  for(;;) {
#ifdef HAVE_GSSAPI
    conn->data_prot = PROT_CMD;
#endif
    result = Curl_write(conn, conn->sock[FIRSTSOCKET], sptr, write_len,
                        &bytes_written);
#ifdef HAVE_GSSAPI
    DEBUGASSERT(data_sec > PROT_NONE && data_sec < PROT_LAST);
    conn->data_prot = data_sec;
#endif

    if(result)
      break;

    if(conn->data->set.verbose)
      Curl_debug(conn->data, CURLINFO_HEADER_OUT, sptr, (size_t)bytes_written);

    if(bytes_written != (ssize_t)write_len) {
      write_len -= bytes_written;
      sptr += bytes_written;
    }
    else
      break;
  }

  return result;
}