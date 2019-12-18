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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nouveau_i2c {int /*<<< orphan*/  (* find ) (struct nouveau_i2c*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* find_type ) (struct nouveau_i2c*,int /*<<< orphan*/ ) ;} ;
struct nouveau_dp_func {int dummy; } ;
struct nouveau_disp {int dummy; } ;
struct nouveau_bios {int dummy; } ;
struct dp_state {int head; int* dpcd; int link_nr; int link_bw; int /*<<< orphan*/  stat; int /*<<< orphan*/  aux; int /*<<< orphan*/  info; int /*<<< orphan*/  version; struct dcb_output* outp; struct nouveau_dp_func const* func; struct nouveau_disp* disp; } ;
struct dcb_output {int /*<<< orphan*/  i2c_index; int /*<<< orphan*/  extdev; scalar_t__ location; int /*<<< orphan*/  hashm; int /*<<< orphan*/  hasht; } ;

/* Variables and functions */
 int DPCD_RC02_MAX_LANE_COUNT ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  NV_I2C_TYPE_DCBI2C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_I2C_TYPE_EXTAUX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_link_train_cr (struct dp_state*) ; 
 int /*<<< orphan*/  dp_link_train_eq (struct dp_state*) ; 
 int /*<<< orphan*/  dp_link_train_fini (struct dp_state*) ; 
 int /*<<< orphan*/  dp_link_train_init (struct dp_state*,int) ; 
 int dp_set_link_config (struct dp_state*) ; 
 int /*<<< orphan*/  dp_set_training_pattern (struct dp_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 struct nouveau_bios* nouveau_bios (struct nouveau_disp*) ; 
 struct nouveau_i2c* nouveau_i2c (struct nouveau_disp*) ; 
 int nv_rdaux (int /*<<< orphan*/ ,int,int*,int) ; 
 int nvbios_dpout_match (struct nouveau_bios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_i2c*,int /*<<< orphan*/ ) ; 

int
nouveau_dp_train(struct nouveau_disp *disp, const struct nouveau_dp_func *func,
		 struct dcb_output *outp, int head, u32 datarate)
{
	struct nouveau_bios *bios = nouveau_bios(disp);
	struct nouveau_i2c *i2c = nouveau_i2c(disp);
	struct dp_state _dp = {
		.disp = disp,
		.func = func,
		.outp = outp,
		.head = head,
	}, *dp = &_dp;
	const u32 bw_list[] = { 270000, 162000, 0 };
	const u32 *link_bw = bw_list;
	u8  hdr, cnt, len;
	u32 data;
	int ret;

	/* find the bios displayport data relevant to this output */
	data = nvbios_dpout_match(bios, outp->hasht, outp->hashm, &dp->version,
				 &hdr, &cnt, &len, &dp->info);
	if (!data) {
		ERR("bios data not found\n");
		return -EINVAL;
	}

	/* acquire the aux channel and fetch some info about the display */
	if (outp->location)
		dp->aux = i2c->find_type(i2c, NV_I2C_TYPE_EXTAUX(outp->extdev));
	else
		dp->aux = i2c->find(i2c, NV_I2C_TYPE_DCBI2C(outp->i2c_index));
	if (!dp->aux) {
		ERR("no aux channel?!\n");
		return -ENODEV;
	}

	ret = nv_rdaux(dp->aux, 0x00000, dp->dpcd, sizeof(dp->dpcd));
	if (ret) {
		ERR("failed to read DPCD\n");
		return ret;
	}

	/* adjust required bandwidth for 8B/10B coding overhead */
	datarate = (datarate / 8) * 10;

	/* enable down-spreading and execute pre-train script from vbios */
	dp_link_train_init(dp, dp->dpcd[3] & 0x01);

	/* start off at highest link rate supported by encoder and display */
	while (*link_bw > (dp->dpcd[1] * 27000))
		link_bw++;

	while (link_bw[0]) {
		/* find minimum required lane count at this link rate */
		dp->link_nr = dp->dpcd[2] & DPCD_RC02_MAX_LANE_COUNT;
		while ((dp->link_nr >> 1) * link_bw[0] > datarate)
			dp->link_nr >>= 1;

		/* drop link rate to minimum with this lane count */
		while ((link_bw[1] * dp->link_nr) > datarate)
			link_bw++;
		dp->link_bw = link_bw[0];

		/* program selected link configuration */
		ret = dp_set_link_config(dp);
		if (ret == 0) {
			/* attempt to train the link at this configuration */
			memset(dp->stat, 0x00, sizeof(dp->stat));
			if (!dp_link_train_cr(dp) &&
			    !dp_link_train_eq(dp))
				break;
		} else
		if (ret >= 1) {
			/* dp_set_link_config() handled training */
			break;
		}

		/* retry at lower rate */
		link_bw++;
	}

	/* finish link training */
	dp_set_training_pattern(dp, 0);

	/* execute post-train script from vbios */
	dp_link_train_fini(dp);
	return true;
}