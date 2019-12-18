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
typedef  scalar_t__ u8 ;
typedef  unsigned int u16 ;
struct ar9300_eeprom {scalar_t__** ctl_freqbin_2G; scalar_t__** ctl_freqbin_5G; } ;

/* Variables and functions */
 scalar_t__ AR5416_BCHAN_UNUSED ; 
 unsigned int AR9300_NUM_BAND_EDGES_2G ; 
 unsigned int AR9300_NUM_BAND_EDGES_5G ; 
 unsigned int MAX_RATE_POWER ; 
 unsigned int ar9003_hw_get_direct_edge_power (struct ar9300_eeprom*,int,unsigned int,int) ; 
 unsigned int ar9003_hw_get_indirect_edge_power (struct ar9300_eeprom*,int,unsigned int,unsigned int,int) ; 
 unsigned int ath9k_hw_fbin2freq (scalar_t__,int) ; 

__attribute__((used)) static u16 ar9003_hw_get_max_edge_power(struct ar9300_eeprom *eep,
					u16 freq, int idx, bool is2GHz)
{
	u16 twiceMaxEdgePower = MAX_RATE_POWER;
	u8 *ctl_freqbin = is2GHz ?
		&eep->ctl_freqbin_2G[idx][0] :
		&eep->ctl_freqbin_5G[idx][0];
	u16 num_edges = is2GHz ?
		AR9300_NUM_BAND_EDGES_2G : AR9300_NUM_BAND_EDGES_5G;
	unsigned int edge;

	/* Get the edge power */
	for (edge = 0;
	     (edge < num_edges) && (ctl_freqbin[edge] != AR5416_BCHAN_UNUSED);
	     edge++) {
		/*
		 * If there's an exact channel match or an inband flag set
		 * on the lower channel use the given rdEdgePower
		 */
		if (freq == ath9k_hw_fbin2freq(ctl_freqbin[edge], is2GHz)) {
			twiceMaxEdgePower =
				ar9003_hw_get_direct_edge_power(eep, idx,
								edge, is2GHz);
			break;
		} else if ((edge > 0) &&
			   (freq < ath9k_hw_fbin2freq(ctl_freqbin[edge],
						      is2GHz))) {
			twiceMaxEdgePower =
				ar9003_hw_get_indirect_edge_power(eep, idx,
								  edge, freq,
								  is2GHz);
			/*
			 * Leave loop - no more affecting edges possible in
			 * this monotonic increasing list
			 */
			break;
		}
	}
	return twiceMaxEdgePower;
}