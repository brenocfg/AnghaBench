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
typedef  int /*<<< orphan*/  lithium_t ;

/* Variables and functions */
#define  AFMT_A_LAW 132 
#define  AFMT_MU_LAW 131 
#define  AFMT_S16_LE 130 
#define  AFMT_S8 129 
#define  AFMT_U8 128 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBGEV (char*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  DBGPV (char*,int,int) ; 
 int /*<<< orphan*/  ad1843_C1C ; 
 int /*<<< orphan*/  ad1843_DA1F ; 
 int /*<<< orphan*/  ad1843_DA1SM ; 
 int /*<<< orphan*/  ad1843_write_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ad1843_write_multi (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ad1843_setup_dac(lithium_t *lith,
			     int framerate,
			     int fmt,
			     int channels)
{
	int ad_fmt = 0, ad_mode = 0;

	DBGEV("(lith=0x%p, framerate=%d, fmt=%d, channels=%d)\n",
	      lith, framerate, fmt, channels);

	switch (fmt) {
	case AFMT_S8:		ad_fmt = 1; break;
	case AFMT_U8:		ad_fmt = 1; break;
	case AFMT_S16_LE:	ad_fmt = 1; break;
	case AFMT_MU_LAW:	ad_fmt = 2; break;
	case AFMT_A_LAW:	ad_fmt = 3; break;
	default:		ASSERT(0);
	}

	switch (channels) {
	case 2:			ad_mode = 0; break;
	case 1:			ad_mode = 1; break;
	default:		ASSERT(0);
	}
		
	DBGPV("ad_mode = %d, ad_fmt = %d\n", ad_mode, ad_fmt);
	ASSERT(framerate >= 4000 && framerate <= 49000);
	ad1843_write_bits(lith, &ad1843_C1C, framerate);
	ad1843_write_multi(lith, 2,
			   &ad1843_DA1SM, ad_mode, &ad1843_DA1F, ad_fmt);
}