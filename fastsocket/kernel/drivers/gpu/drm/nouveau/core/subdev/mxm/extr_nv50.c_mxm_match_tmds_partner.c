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
typedef  int /*<<< orphan*/  u8 ;
struct nouveau_mxm {int dummy; } ;
struct mxms_odev {int outp_type; scalar_t__ dig_conn; } ;
struct TYPE_2__ {scalar_t__ dig_conn; } ;
struct context {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mxms_output_device (struct nouveau_mxm*,int /*<<< orphan*/ *,struct mxms_odev*) ; 

__attribute__((used)) static bool
mxm_match_tmds_partner(struct nouveau_mxm *mxm, u8 *data, void *info)
{
	struct context *ctx = info;
	struct mxms_odev desc;

	mxms_output_device(mxm, data, &desc);
	if (desc.outp_type == 2 &&
	    desc.dig_conn == ctx->desc.dig_conn)
		return false;
	return true;
}