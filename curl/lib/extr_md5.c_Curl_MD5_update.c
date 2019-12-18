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
struct TYPE_5__ {int /*<<< orphan*/  md5_hashctx; TYPE_1__* md5_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* md5_update_func ) (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ;} ;
typedef  TYPE_2__ MD5_context ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

CURLcode Curl_MD5_update(MD5_context *context,
                         const unsigned char *data,
                         unsigned int len)
{
  (*context->md5_hash->md5_update_func)(context->md5_hashctx, data, len);

  return CURLE_OK;
}