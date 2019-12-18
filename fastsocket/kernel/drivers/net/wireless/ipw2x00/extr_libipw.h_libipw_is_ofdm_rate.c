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

/* Variables and functions */
 int LIBIPW_BASIC_RATE_MASK ; 
#define  LIBIPW_OFDM_RATE_12MB 135 
#define  LIBIPW_OFDM_RATE_18MB 134 
#define  LIBIPW_OFDM_RATE_24MB 133 
#define  LIBIPW_OFDM_RATE_36MB 132 
#define  LIBIPW_OFDM_RATE_48MB 131 
#define  LIBIPW_OFDM_RATE_54MB 130 
#define  LIBIPW_OFDM_RATE_6MB 129 
#define  LIBIPW_OFDM_RATE_9MB 128 

__attribute__((used)) static inline int libipw_is_ofdm_rate(u8 rate)
{
	switch (rate & ~LIBIPW_BASIC_RATE_MASK) {
	case LIBIPW_OFDM_RATE_6MB:
	case LIBIPW_OFDM_RATE_9MB:
	case LIBIPW_OFDM_RATE_12MB:
	case LIBIPW_OFDM_RATE_18MB:
	case LIBIPW_OFDM_RATE_24MB:
	case LIBIPW_OFDM_RATE_36MB:
	case LIBIPW_OFDM_RATE_48MB:
	case LIBIPW_OFDM_RATE_54MB:
		return 1;
	}
	return 0;
}