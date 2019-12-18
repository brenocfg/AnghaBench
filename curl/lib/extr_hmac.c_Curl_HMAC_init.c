#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* hmac_hashctxt2; void* hmac_hashctxt1; TYPE_1__ const* hmac_hash; } ;
struct TYPE_6__ {int hmac_ctxtsize; int hmac_resultlen; unsigned int hmac_maxkeylen; int /*<<< orphan*/  (* hmac_hupdate ) (void*,int*,int) ;int /*<<< orphan*/  (* hmac_hinit ) (void*) ;int /*<<< orphan*/  (* hmac_hfinal ) (unsigned char*,void*) ;} ;
typedef  TYPE_1__ HMAC_params ;
typedef  TYPE_2__ HMAC_context ;

/* Variables and functions */
 unsigned char const hmac_ipad ; 
 int hmac_opad ; 
 TYPE_2__* malloc (size_t) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 
 int /*<<< orphan*/  stub5 (void*) ; 
 int /*<<< orphan*/  stub6 (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub7 (void*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub8 (void*,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub9 (void*,int*,int) ; 

HMAC_context *
Curl_HMAC_init(const HMAC_params * hashparams,
               const unsigned char *key,
               unsigned int keylen)
{
  size_t i;
  HMAC_context *ctxt;
  unsigned char *hkey;
  unsigned char b;

  /* Create HMAC context. */
  i = sizeof(*ctxt) + 2 * hashparams->hmac_ctxtsize +
    hashparams->hmac_resultlen;
  ctxt = malloc(i);

  if(!ctxt)
    return ctxt;

  ctxt->hmac_hash = hashparams;
  ctxt->hmac_hashctxt1 = (void *) (ctxt + 1);
  ctxt->hmac_hashctxt2 = (void *) ((char *) ctxt->hmac_hashctxt1 +
      hashparams->hmac_ctxtsize);

  /* If the key is too long, replace it by its hash digest. */
  if(keylen > hashparams->hmac_maxkeylen) {
    (*hashparams->hmac_hinit)(ctxt->hmac_hashctxt1);
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt1, key, keylen);
    hkey = (unsigned char *) ctxt->hmac_hashctxt2 + hashparams->hmac_ctxtsize;
    (*hashparams->hmac_hfinal)(hkey, ctxt->hmac_hashctxt1);
    key = hkey;
    keylen = hashparams->hmac_resultlen;
  }

  /* Prime the two hash contexts with the modified key. */
  (*hashparams->hmac_hinit)(ctxt->hmac_hashctxt1);
  (*hashparams->hmac_hinit)(ctxt->hmac_hashctxt2);

  for(i = 0; i < keylen; i++) {
    b = (unsigned char)(*key ^ hmac_ipad);
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt1, &b, 1);
    b = (unsigned char)(*key++ ^ hmac_opad);
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt2, &b, 1);
  }

  for(; i < hashparams->hmac_maxkeylen; i++) {
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt1, &hmac_ipad, 1);
    (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt2, &hmac_opad, 1);
  }

  /* Done, return pointer to HMAC context. */
  return ctxt;
}