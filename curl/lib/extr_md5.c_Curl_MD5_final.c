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
struct TYPE_7__ {struct TYPE_7__* md5_hashctx; TYPE_1__* md5_hash; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* md5_final_func ) (unsigned char*,TYPE_2__*) ;} ;
typedef  TYPE_2__ MD5_context ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,TYPE_2__*) ; 

CURLcode Curl_MD5_final(MD5_context *context, unsigned char *result)
{
  (*context->md5_hash->md5_final_func)(result, context->md5_hashctx);

  free(context->md5_hashctx);
  free(context);

  return CURLE_OK;
}