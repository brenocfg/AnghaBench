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
struct libipw_device {int modulation; int freq_band; } ;

/* Variables and functions */
 int IEEE_A ; 
 int IEEE_B ; 
 int IEEE_G ; 
 int LIBIPW_24GHZ_BAND ; 
 int LIBIPW_52GHZ_BAND ; 
 int LIBIPW_CCK_MODULATION ; 
 int LIBIPW_OFDM_MODULATION ; 

__attribute__((used)) static inline int libipw_is_valid_mode(struct libipw_device *ieee,
					  int mode)
{
	/*
	 * It is possible for both access points and our device to support
	 * combinations of modes, so as long as there is one valid combination
	 * of ap/device supported modes, then return success
	 *
	 */
	if ((mode & IEEE_A) &&
	    (ieee->modulation & LIBIPW_OFDM_MODULATION) &&
	    (ieee->freq_band & LIBIPW_52GHZ_BAND))
		return 1;

	if ((mode & IEEE_G) &&
	    (ieee->modulation & LIBIPW_OFDM_MODULATION) &&
	    (ieee->freq_band & LIBIPW_24GHZ_BAND))
		return 1;

	if ((mode & IEEE_B) &&
	    (ieee->modulation & LIBIPW_CCK_MODULATION) &&
	    (ieee->freq_band & LIBIPW_24GHZ_BAND))
		return 1;

	return 0;
}