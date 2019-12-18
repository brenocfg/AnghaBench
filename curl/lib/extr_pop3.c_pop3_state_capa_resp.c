#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int authmechs; } ;
struct pop3_conn {int /*<<< orphan*/  authtypes; scalar_t__ tls_supported; TYPE_3__ sasl; } ;
struct TYPE_6__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_4__* ssl; TYPE_1__ proto; struct Curl_easy* data; } ;
struct TYPE_10__ {scalar_t__ use_ssl; } ;
struct TYPE_7__ {char* buffer; } ;
struct Curl_easy {TYPE_5__ set; TYPE_2__ state; } ;
typedef  int /*<<< orphan*/  pop3state ;
struct TYPE_9__ {int /*<<< orphan*/  use; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_USE_SSL_FAILED ; 
 scalar_t__ CURLUSESSL_TRY ; 
 unsigned int Curl_sasl_decode_mech (char const*,size_t,size_t*) ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  POP3_TYPE_CLEARTEXT ; 
 int /*<<< orphan*/  POP3_TYPE_SASL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  pop3_perform_authentication (struct connectdata*) ; 
 int /*<<< orphan*/  pop3_perform_starttls (struct connectdata*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static CURLcode pop3_state_capa_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *line = data->state.buffer;
  size_t len = strlen(line);

  (void)instate; /* no use for this yet */

  /* Do we have a untagged continuation response? */
  if(pop3code == '*') {
    /* Does the server support the STLS capability? */
    if(len >= 4 && !memcmp(line, "STLS", 4))
      pop3c->tls_supported = TRUE;

    /* Does the server support clear text authentication? */
    else if(len >= 4 && !memcmp(line, "USER", 4))
      pop3c->authtypes |= POP3_TYPE_CLEARTEXT;

    /* Does the server support SASL based authentication? */
    else if(len >= 5 && !memcmp(line, "SASL ", 5)) {
      pop3c->authtypes |= POP3_TYPE_SASL;

      /* Advance past the SASL keyword */
      line += 5;
      len -= 5;

      /* Loop through the data line */
      for(;;) {
        size_t llen;
        size_t wordlen;
        unsigned int mechbit;

        while(len &&
              (*line == ' ' || *line == '\t' ||
               *line == '\r' || *line == '\n')) {

          line++;
          len--;
        }

        if(!len)
          break;

        /* Extract the word */
        for(wordlen = 0; wordlen < len && line[wordlen] != ' ' &&
              line[wordlen] != '\t' && line[wordlen] != '\r' &&
              line[wordlen] != '\n';)
          wordlen++;

        /* Test the word for a matching authentication mechanism */
        mechbit = Curl_sasl_decode_mech(line, wordlen, &llen);
        if(mechbit && llen == wordlen)
          pop3c->sasl.authmechs |= mechbit;

        line += wordlen;
        len -= wordlen;
      }
    }
  }
  else if(pop3code == '+') {
    if(data->set.use_ssl && !conn->ssl[FIRSTSOCKET].use) {
      /* We don't have a SSL/TLS connection yet, but SSL is requested */
      if(pop3c->tls_supported)
        /* Switch to TLS connection now */
        result = pop3_perform_starttls(conn);
      else if(data->set.use_ssl == CURLUSESSL_TRY)
        /* Fallback and carry on with authentication */
        result = pop3_perform_authentication(conn);
      else {
        failf(data, "STLS not supported.");
        result = CURLE_USE_SSL_FAILED;
      }
    }
    else
      result = pop3_perform_authentication(conn);
  }
  else {
    /* Clear text is supported when CAPA isn't recognised */
    pop3c->authtypes |= POP3_TYPE_CLEARTEXT;

    result = pop3_perform_authentication(conn);
  }

  return result;
}