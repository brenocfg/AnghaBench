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
struct ccdigest_info {int dummy; } ;
typedef  int /*<<< orphan*/  cchmac_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccdigest_update (struct ccdigest_info const*,int /*<<< orphan*/ ,size_t,void const*) ; 
 int /*<<< orphan*/  cchmac_digest_ctx (struct ccdigest_info const*,int /*<<< orphan*/ ) ; 

void cchmac_update(const struct ccdigest_info *di, cchmac_ctx_t hc,
                   size_t data_len, const void *data) {
    ccdigest_update(di, cchmac_digest_ctx(di, hc), data_len, data);
}