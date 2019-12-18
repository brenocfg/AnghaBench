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
struct rme96 {int* vol; } ;

/* Variables and functions */
 scalar_t__ RME96_DAC_IS_1852 (struct rme96*) ; 
 scalar_t__ RME96_DAC_IS_1855 (struct rme96*) ; 
 int /*<<< orphan*/  snd_rme96_write_SPI (struct rme96*,int) ; 

__attribute__((used)) static void
snd_rme96_apply_dac_volume(struct rme96 *rme96)
{
	if (RME96_DAC_IS_1852(rme96)) {
		snd_rme96_write_SPI(rme96, (rme96->vol[0] << 2) | 0x0);
		snd_rme96_write_SPI(rme96, (rme96->vol[1] << 2) | 0x2);
	} else if (RME96_DAC_IS_1855(rme96)) {
		snd_rme96_write_SPI(rme96, (rme96->vol[0] & 0x3FF) | 0x000);
		snd_rme96_write_SPI(rme96, (rme96->vol[1] & 0x3FF) | 0x400);
	}
}