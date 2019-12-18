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
struct TYPE_7__ {void* md5_hashctx; TYPE_1__ const* md5_hash; } ;
struct TYPE_6__ {int md5_ctxtsize; int /*<<< orphan*/  (* md5_init_func ) (void*) ;} ;
typedef  TYPE_1__ MD5_params ;
typedef  TYPE_2__ MD5_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

MD5_context *Curl_MD5_init(const MD5_params *md5params)
{
  MD5_context *ctxt;

  /* Create MD5 context */
  ctxt = malloc(sizeof(*ctxt));

  if(!ctxt)
    return ctxt;

  ctxt->md5_hashctx = malloc(md5params->md5_ctxtsize);

  if(!ctxt->md5_hashctx) {
    free(ctxt);
    return NULL;
  }

  ctxt->md5_hash = md5params;

  (*md5params->md5_init_func)(ctxt->md5_hashctx);

  return ctxt;
}