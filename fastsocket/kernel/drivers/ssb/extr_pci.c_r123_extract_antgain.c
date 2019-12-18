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
typedef  int u16 ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t SPOFF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSB_SPROM1_AGAIN ; 

__attribute__((used)) static s8 r123_extract_antgain(u8 sprom_revision, const u16 *in,
			       u16 mask, u16 shift)
{
	u16 v;
	u8 gain;

	v = in[SPOFF(SSB_SPROM1_AGAIN)];
	gain = (v & mask) >> shift;
	if (gain == 0xFF)
		gain = 2; /* If unset use 2dBm */
	if (sprom_revision == 1) {
		/* Convert to Q5.2 */
		gain <<= 2;
	} else {
		/* Q5.2 Fractional part is stored in 0xC0 */
		gain = ((gain & 0xC0) >> 6) | ((gain & 0x3F) << 2);
	}

	return (s8)gain;
}