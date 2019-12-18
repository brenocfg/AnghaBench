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
typedef  int u8 ;
typedef  int u32 ;
struct ar9170_calctl_edges {int channel; int power_flags; } ;
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int AR5416_MAX_RATE_POWER ; 
 int AR5416_NUM_BAND_EDGES ; 
 int AR9170_CALCTL_EDGE_FLAGS ; 

__attribute__((used)) static u8 carl9170_get_max_edge_power(struct ar9170 *ar,
	u32 freq, struct ar9170_calctl_edges edges[])
{
	int i;
	u8 rc = AR5416_MAX_RATE_POWER;
	u8 f;
	if (freq < 3000)
		f = freq - 2300;
	else
		f = (freq - 4800) / 5;

	for (i = 0; i < AR5416_NUM_BAND_EDGES; i++) {
		if (edges[i].channel == 0xff)
			break;
		if (f == edges[i].channel) {
			/* exact freq match */
			rc = edges[i].power_flags & ~AR9170_CALCTL_EDGE_FLAGS;
			break;
		}
		if (i > 0 && f < edges[i].channel) {
			if (f > edges[i - 1].channel &&
			    edges[i - 1].power_flags &
			    AR9170_CALCTL_EDGE_FLAGS) {
				/* lower channel has the inband flag set */
				rc = edges[i - 1].power_flags &
					~AR9170_CALCTL_EDGE_FLAGS;
			}
			break;
		}
	}

	if (i == AR5416_NUM_BAND_EDGES) {
		if (f > edges[i - 1].channel &&
		    edges[i - 1].power_flags & AR9170_CALCTL_EDGE_FLAGS) {
			/* lower channel has the inband flag set */
			rc = edges[i - 1].power_flags &
				~AR9170_CALCTL_EDGE_FLAGS;
		}
	}
	return rc;
}