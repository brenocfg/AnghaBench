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
struct pop3_conn {int /*<<< orphan*/  pp; scalar_t__ apoptimestamp; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_passwd; } ;
struct TYPE_3__ {struct pop3_conn pop3c; } ;
struct connectdata {int /*<<< orphan*/  user; scalar_t__ passwd; TYPE_2__ bits; TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  MD5_context ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  Curl_DIGEST_MD5 ; 
 int /*<<< orphan*/  Curl_MD5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/ * Curl_MD5_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_MD5_update (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int MD5_DIGEST_LEN ; 
 int /*<<< orphan*/  POP3_APOP ; 
 int /*<<< orphan*/  POP3_STOP ; 
 int /*<<< orphan*/  curlx_uztoui (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,unsigned char) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static CURLcode pop3_perform_apop(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  size_t i;
  MD5_context *ctxt;
  unsigned char digest[MD5_DIGEST_LEN];
  char secret[2 * MD5_DIGEST_LEN + 1];

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Create the digest */
  ctxt = Curl_MD5_init(Curl_DIGEST_MD5);
  if(!ctxt)
    return CURLE_OUT_OF_MEMORY;

  Curl_MD5_update(ctxt, (const unsigned char *) pop3c->apoptimestamp,
                  curlx_uztoui(strlen(pop3c->apoptimestamp)));

  Curl_MD5_update(ctxt, (const unsigned char *) conn->passwd,
                  curlx_uztoui(strlen(conn->passwd)));

  /* Finalise the digest */
  Curl_MD5_final(ctxt, digest);

  /* Convert the calculated 16 octet digest into a 32 byte hex string */
  for(i = 0; i < MD5_DIGEST_LEN; i++)
    msnprintf(&secret[2 * i], 3, "%02x", digest[i]);

  result = Curl_pp_sendf(&pop3c->pp, "APOP %s %s", conn->user, secret);

  if(!result)
    state(conn, POP3_APOP);

  return result;
}