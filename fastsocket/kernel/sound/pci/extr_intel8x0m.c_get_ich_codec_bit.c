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
struct intel8x0m {int dummy; } ;

/* Variables and functions */
#define  ICH_PCR 130 
#define  ICH_SCR 129 
#define  ICH_TCR 128 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static unsigned int get_ich_codec_bit(struct intel8x0m *chip, unsigned int codec)
{
	static unsigned int codec_bit[3] = {
		ICH_PCR, ICH_SCR, ICH_TCR
	};
	if (snd_BUG_ON(codec >= 3))
		return ICH_PCR;
	return codec_bit[codec];
}