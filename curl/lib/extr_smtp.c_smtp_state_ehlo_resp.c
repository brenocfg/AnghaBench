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
struct smtp_conn {void* tls_supported; TYPE_3__ sasl; void* auth_supported; void* size_supported; } ;
struct TYPE_6__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_4__* ssl; TYPE_1__ proto; struct Curl_easy* data; } ;
struct TYPE_10__ {scalar_t__ use_ssl; } ;
struct TYPE_7__ {char* buffer; } ;
struct Curl_easy {TYPE_5__ set; TYPE_2__ state; } ;
typedef  int /*<<< orphan*/  smtpstate ;
struct TYPE_9__ {scalar_t__ use; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_REMOTE_ACCESS_DENIED ; 
 int /*<<< orphan*/  CURLE_USE_SSL_FAILED ; 
 int /*<<< orphan*/  CURLE_WEIRD_SERVER_REPLY ; 
 scalar_t__ CURLUSESSL_TRY ; 
 unsigned int Curl_sasl_decode_mech (char const*,size_t,size_t*) ; 
 size_t FIRSTSOCKET ; 
 void* TRUE ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,...) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  smtp_perform_authentication (struct connectdata*) ; 
 int /*<<< orphan*/  smtp_perform_helo (struct connectdata*) ; 
 int /*<<< orphan*/  smtp_perform_starttls (struct connectdata*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static CURLcode smtp_state_ehlo_resp(struct connectdata *conn, int smtpcode,
                                     smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  const char *line = data->state.buffer;
  size_t len = strlen(line);

  (void)instate; /* no use for this yet */

  if(smtpcode/100 != 2 && smtpcode != 1) {
    if(data->set.use_ssl <= CURLUSESSL_TRY || conn->ssl[FIRSTSOCKET].use)
      result = smtp_perform_helo(conn);
    else {
      failf(data, "Remote access denied: %d", smtpcode);
      result = CURLE_REMOTE_ACCESS_DENIED;
    }
  }
  else if(len >= 4) {
    line += 4;
    len -= 4;

    /* Does the server support the STARTTLS capability? */
    if(len >= 8 && !memcmp(line, "STARTTLS", 8))
      smtpc->tls_supported = TRUE;

    /* Does the server support the SIZE capability? */
    else if(len >= 4 && !memcmp(line, "SIZE", 4))
      smtpc->size_supported = TRUE;

    /* Does the server support authentication? */
    else if(len >= 5 && !memcmp(line, "AUTH ", 5)) {
      smtpc->auth_supported = TRUE;

      /* Advance past the AUTH keyword */
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
          smtpc->sasl.authmechs |= mechbit;

        line += wordlen;
        len -= wordlen;
      }
    }

    if(smtpcode != 1) {
      if(data->set.use_ssl && !conn->ssl[FIRSTSOCKET].use) {
        /* We don't have a SSL/TLS connection yet, but SSL is requested */
        if(smtpc->tls_supported)
          /* Switch to TLS connection now */
          result = smtp_perform_starttls(conn);
        else if(data->set.use_ssl == CURLUSESSL_TRY)
          /* Fallback and carry on with authentication */
          result = smtp_perform_authentication(conn);
        else {
          failf(data, "STARTTLS not supported.");
          result = CURLE_USE_SSL_FAILED;
        }
      }
      else
        result = smtp_perform_authentication(conn);
    }
  }
  else {
    failf(data, "Unexpectedly short EHLO response");
    result = CURLE_WEIRD_SERVER_REPLY;
  }

  return result;
}