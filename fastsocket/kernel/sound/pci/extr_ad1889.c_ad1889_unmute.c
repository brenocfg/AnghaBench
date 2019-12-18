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
typedef  int u16 ;
struct snd_ad1889 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_DS_WADA ; 
 int AD_DS_WADA_LWAM ; 
 int AD_DS_WADA_RWAM ; 
 int ad1889_readw (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1889_writew (struct snd_ad1889*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
ad1889_unmute(struct snd_ad1889 *chip)
{
	u16 st;
	st = ad1889_readw(chip, AD_DS_WADA) & 
		~(AD_DS_WADA_RWAM | AD_DS_WADA_LWAM);
	ad1889_writew(chip, AD_DS_WADA, st);
	ad1889_readw(chip, AD_DS_WADA);
}