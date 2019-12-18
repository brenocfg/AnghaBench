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
typedef  int u64 ;
typedef  int u32 ;
struct sbridge_pvt {int tolm; int tohm; int /*<<< orphan*/ * pci_tad; TYPE_1__* channel; int /*<<< orphan*/  pci_ha0; int /*<<< orphan*/  pci_sad0; int /*<<< orphan*/  pci_sad1; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dimms; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_RULE_ENABLE (int) ; 
 int GET_TOHM (int) ; 
 int GET_TOLM (int) ; 
 scalar_t__ INTERLEAVE_MODE (int) ; 
 int /*<<< orphan*/  IS_RIR_VALID (int) ; 
 int MAX_RIR_RANGES ; 
 int MAX_SAD ; 
 int MAX_TAD ; 
 int NUM_CHANNELS ; 
 int RIR_LIMIT (int) ; 
 int RIR_OFFSET (int) ; 
 scalar_t__ RIR_RNK_TGT (int) ; 
 int RIR_WAY (int) ; 
 int SAD_LIMIT (int) ; 
 scalar_t__ TAD_CH (int) ; 
 int TAD_LIMIT (int) ; 
 int TAD_OFFSET (int) ; 
 scalar_t__ TAD_SOCK (int) ; 
 scalar_t__ TAD_TGT0 (int) ; 
 scalar_t__ TAD_TGT1 (int) ; 
 scalar_t__ TAD_TGT2 (int) ; 
 scalar_t__ TAD_TGT3 (int) ; 
 int /*<<< orphan*/  TOHM ; 
 int /*<<< orphan*/  TOLM ; 
 int /*<<< orphan*/  debugf0 (char*,int,int,int,...) ; 
 int /*<<< orphan*/ * dram_rule ; 
 int /*<<< orphan*/  get_dram_attr (int) ; 
 int /*<<< orphan*/ * interleave_list ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ ** rir_offset ; 
 int /*<<< orphan*/ * rir_way_limit ; 
 int sad_pkg (int,int) ; 
 int /*<<< orphan*/ * tad_ch_nilv_offset ; 
 int /*<<< orphan*/ * tad_dram_rule ; 

__attribute__((used)) static void get_memory_layout(const struct mem_ctl_info *mci)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	int i, j, k, n_sads, n_tads, sad_interl;
	u32 reg;
	u64 limit, prv = 0;
	u64 tmp_mb;
	u32 rir_way;

	/*
	 * Step 1) Get TOLM/TOHM ranges
	 */

	/* Address range is 32:28 */
	pci_read_config_dword(pvt->pci_sad1, TOLM,
			      &reg);
	pvt->tolm = GET_TOLM(reg);
	tmp_mb = (1 + pvt->tolm) >> 20;

	debugf0("TOLM: %Lu.%03Lu GB (0x%016Lx)\n",
		tmp_mb / 1000, tmp_mb % 1000, (u64)pvt->tolm);

	/* Address range is already 45:25 */
	pci_read_config_dword(pvt->pci_sad1, TOHM,
			      &reg);
	pvt->tohm = GET_TOHM(reg);
	tmp_mb = (1 + pvt->tohm) >> 20;

	debugf0("TOHM: %Lu.%03Lu GB (0x%016Lx)",
		tmp_mb / 1000, tmp_mb % 1000, (u64)pvt->tohm);

	/*
	 * Step 2) Get SAD range and SAD Interleave list
	 * TAD registers contain the interleave wayness. However, it
	 * seems simpler to just discover it indirectly, with the
	 * algorithm bellow.
	 */
	prv = 0;
	for (n_sads = 0; n_sads < MAX_SAD; n_sads++) {
		/* SAD_LIMIT Address range is 45:26 */
		pci_read_config_dword(pvt->pci_sad0, dram_rule[n_sads],
				      &reg);
		limit = SAD_LIMIT(reg);

		if (!DRAM_RULE_ENABLE(reg))
			continue;

		if (limit <= prv)
			break;

		tmp_mb = (limit + 1) >> 20;
		debugf0("SAD#%d %s up to %Lu.%03Lu GB (0x%016Lx) %s reg=0x%08x\n",
			n_sads,
			get_dram_attr(reg),
			tmp_mb / 1000, tmp_mb % 1000,
			((u64)tmp_mb) << 20L,
			INTERLEAVE_MODE(reg) ? "Interleave: 8:6" : "Interleave: [8:6]XOR[18:16]",
			reg);
		prv = limit;

		pci_read_config_dword(pvt->pci_sad0, interleave_list[n_sads],
				      &reg);
		sad_interl = sad_pkg(reg, 0);
		for (j = 0; j < 8; j++) {
			if (j > 0 && sad_interl == sad_pkg(reg, j))
				break;

			debugf0("SAD#%d, interleave #%d: %d\n",
			n_sads, j, sad_pkg(reg, j));
		}
	}

	/*
	 * Step 3) Get TAD range
	 */
	prv = 0;
	for (n_tads = 0; n_tads < MAX_TAD; n_tads++) {
		pci_read_config_dword(pvt->pci_ha0, tad_dram_rule[n_tads],
				      &reg);
		limit = TAD_LIMIT(reg);
		if (limit <= prv)
			break;
		tmp_mb = (limit + 1) >> 20;

		debugf0("TAD#%d: up to %Lu.%03Lu GB (0x%016Lx), socket interleave %d, memory interleave %d, TGT: %d, %d, %d, %d, reg=0x%08x\n",
			n_tads, tmp_mb / 1000, tmp_mb % 1000,
			((u64)tmp_mb) << 20L,
			(u32)TAD_SOCK(reg),
			(u32)TAD_CH(reg),
			(u32)TAD_TGT0(reg),
			(u32)TAD_TGT1(reg),
			(u32)TAD_TGT2(reg),
			(u32)TAD_TGT3(reg),
			reg);
		prv = tmp_mb;
	}

	/*
	 * Step 4) Get TAD offsets, per each channel
	 */
	for (i = 0; i < NUM_CHANNELS; i++) {
		if (!pvt->channel[i].dimms)
			continue;
		for (j = 0; j < n_tads; j++) {
			pci_read_config_dword(pvt->pci_tad[i],
					      tad_ch_nilv_offset[j],
					      &reg);
			tmp_mb = TAD_OFFSET(reg) >> 20;
			debugf0("TAD CH#%d, offset #%d: %Lu.%03Lu GB (0x%016Lx), reg=0x%08x\n",
				i, j,
				tmp_mb / 1000, tmp_mb % 1000,
				((u64)tmp_mb) << 20L,
				reg);
		}
	}

	/*
	 * Step 6) Get RIR Wayness/Limit, per each channel
	 */
	for (i = 0; i < NUM_CHANNELS; i++) {
		if (!pvt->channel[i].dimms)
			continue;
		for (j = 0; j < MAX_RIR_RANGES; j++) {
			pci_read_config_dword(pvt->pci_tad[i],
					      rir_way_limit[j],
					      &reg);

			if (!IS_RIR_VALID(reg))
				continue;

			tmp_mb = RIR_LIMIT(reg) >> 20;
			rir_way = 1 << RIR_WAY(reg);
			debugf0("CH#%d RIR#%d, limit: %Lu.%03Lu GB (0x%016Lx), way: %d, reg=0x%08x\n",
				i, j,
				tmp_mb / 1000, tmp_mb % 1000,
				((u64)tmp_mb) << 20L,
				rir_way,
				reg);

			for (k = 0; k < rir_way; k++) {
				pci_read_config_dword(pvt->pci_tad[i],
						      rir_offset[j][k],
						      &reg);
				tmp_mb = RIR_OFFSET(reg) << 6;

				debugf0("CH#%d RIR#%d INTL#%d, offset %Lu.%03Lu GB (0x%016Lx), tgt: %d, reg=0x%08x\n",
					i, j, k,
					tmp_mb / 1000, tmp_mb % 1000,
					((u64)tmp_mb) << 20L,
					(u32)RIR_RNK_TGT(reg),
					reg);
			}
		}
	}
}