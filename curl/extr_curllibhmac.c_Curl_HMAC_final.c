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
struct TYPE_5__ {scalar_t__ hmac_hashctxt2; scalar_t__ hmac_hashctxt1; TYPE_1__* hmac_hash; } ;
struct TYPE_4__ {int hmac_ctxtsize; int /*<<< orphan*/  (* hmac_hfinal ) (unsigned char*,scalar_t__) ;int /*<<< orphan*/  hmac_resultlen; int /*<<< orphan*/  (* hmac_hupdate ) (scalar_t__,unsigned char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ HMAC_params ;
typedef  TYPE_2__ HMAC_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,scalar_t__) ; 

int Curl_HMAC_final(HMAC_context *ctxt, unsigned char *result)
{
  const HMAC_params * hashparams = ctxt->hmac_hash;

  /* Do not get result if called with a null parameter: only release
     storage. */

  if(!result)
    result = (unsigned char *) ctxt->hmac_hashctxt2 +
     ctxt->hmac_hash->hmac_ctxtsize;

  (*hashparams->hmac_hfinal)(result, ctxt->hmac_hashctxt1);
  (*hashparams->hmac_hupdate)(ctxt->hmac_hashctxt2,
   result, hashparams->hmac_resultlen);
  (*hashparams->hmac_hfinal)(result, ctxt->hmac_hashctxt2);
  free((char *) ctxt);
  return 0;
}