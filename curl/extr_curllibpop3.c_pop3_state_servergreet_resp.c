#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pop3_conn {char* apoptimestamp; int /*<<< orphan*/  authtypes; } ;
struct TYPE_3__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct TYPE_4__ {char* buffer; } ;
struct Curl_easy {TYPE_2__ state; } ;
typedef  int /*<<< orphan*/  pop3state ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_WEIRD_SERVER_REPLY ; 
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  POP3_TYPE_APOP ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  pop3_perform_capa (struct connectdata*) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static CURLcode pop3_state_servergreet_resp(struct connectdata *conn,
                                            int pop3code,
                                            pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *line = data->state.buffer;
  size_t len = strlen(line);

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Got unexpected pop3-server response");
    result = CURLE_WEIRD_SERVER_REPLY;
  }
  else {
    /* Does the server support APOP authentication? */
    if(len >= 4 && line[len - 2] == '>') {
      /* Look for the APOP timestamp */
      size_t i;
      for(i = 3; i < len - 2; ++i) {
        if(line[i] == '<') {
          /* Calculate the length of the timestamp */
          size_t timestamplen = len - 1 - i;
          char *at;
          if(!timestamplen)
            break;

          /* Allocate some memory for the timestamp */
          pop3c->apoptimestamp = (char *)calloc(1, timestamplen + 1);

          if(!pop3c->apoptimestamp)
            break;

          /* Copy the timestamp */
          memcpy(pop3c->apoptimestamp, line + i, timestamplen);
          pop3c->apoptimestamp[timestamplen] = '\0';

          /* If the timestamp does not contain '@' it is not (as required by
             RFC-1939) conformant to the RFC-822 message id syntax, and we
             therefore do not use APOP authentication. */
          at = strchr(pop3c->apoptimestamp, '@');
          if(!at)
            Curl_safefree(pop3c->apoptimestamp);
          else
            /* Store the APOP capability */
            pop3c->authtypes |= POP3_TYPE_APOP;
          break;
        }
      }
    }

    result = pop3_perform_capa(conn);
  }

  return result;
}