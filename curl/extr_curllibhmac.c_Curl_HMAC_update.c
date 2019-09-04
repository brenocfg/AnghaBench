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
struct TYPE_5__ {int /*<<< orphan*/  hmac_hashctxt1; TYPE_1__* hmac_hash; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hmac_hupdate ) (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ;} ;
typedef  TYPE_2__ HMAC_context ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char const*,unsigned int) ; 

int Curl_HMAC_update(HMAC_context * ctxt,
                     const unsigned char *data,
                     unsigned int len)
{
  /* Update first hash calculation. */
  (*ctxt->hmac_hash->hmac_hupdate)(ctxt->hmac_hashctxt1, data, len);
  return 0;
}