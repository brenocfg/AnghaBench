#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* hmac_walker_ctx_t ;
struct TYPE_2__ {int /*<<< orphan*/  hmac_ctx; int /*<<< orphan*/  di; } ;

/* Variables and functions */
 int /*<<< orphan*/  cchmac_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
do_hmac(void *walker, uint8_t *data, uint32_t len)
{
	hmac_walker_ctx_t wctx = (hmac_walker_ctx_t)walker;

	cchmac_update(wctx->di, wctx->hmac_ctx, len, data);

	return (0);
}