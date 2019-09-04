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
struct digestdata {void* userhash; void* stale; int /*<<< orphan*/  algo; scalar_t__ nc; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  qop; int /*<<< orphan*/  opaque; int /*<<< orphan*/  realm; int /*<<< orphan*/  cnonce; int /*<<< orphan*/  nonce; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURLDIGESTALGO_MD5 ; 
 int /*<<< orphan*/  Curl_safefree (int /*<<< orphan*/ ) ; 
 void* FALSE ; 

void Curl_auth_digest_cleanup(struct digestdata *digest)
{
  Curl_safefree(digest->nonce);
  Curl_safefree(digest->cnonce);
  Curl_safefree(digest->realm);
  Curl_safefree(digest->opaque);
  Curl_safefree(digest->qop);
  Curl_safefree(digest->algorithm);

  digest->nc = 0;
  digest->algo = CURLDIGESTALGO_MD5; /* default algorithm */
  digest->stale = FALSE; /* default means normal, not stale */
  digest->userhash = FALSE;
}