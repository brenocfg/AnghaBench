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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_freqReg ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  hdspm_write (struct hdspm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 

__attribute__((used)) static void hdspm_set_dds_value(struct hdspm *hdspm, int rate)
{
	u64 n;
	
	if (rate >= 112000)
		rate /= 4;
	else if (rate >= 56000)
		rate /= 2;

	/* RME says n = 104857600000000, but in the windows MADI driver, I see:
//	return 104857600000000 / rate; // 100 MHz
	return 110100480000000 / rate; // 105 MHz
        */	   
	/* n = 104857600000000ULL; */ /*  =  2^20 * 10^8 */
	n = 110100480000000ULL;    /* Value checked for AES32 and MADI */
	n = div_u64(n, rate);
	/* n should be less than 2^32 for being written to FREQ register */
	snd_BUG_ON(n >> 32);
	hdspm_write(hdspm, HDSPM_freqReg, (u32)n);
}