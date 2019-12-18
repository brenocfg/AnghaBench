#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ skip_load; int /*<<< orphan*/  osdcoretype; int /*<<< orphan*/  videoformattype; int /*<<< orphan*/  cartpath; int /*<<< orphan*/  mpegpath; int /*<<< orphan*/  buppath; int /*<<< orphan*/  cdpath; int /*<<< orphan*/  biospath; scalar_t__ regionid; int /*<<< orphan*/  carttype; int /*<<< orphan*/  cdcoretype; int /*<<< orphan*/  sndcoretype; int /*<<< orphan*/  vidcoretype; int /*<<< orphan*/  sh2coretype; int /*<<< orphan*/  percoretype; int /*<<< orphan*/  m68kcoretype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CART_NONE ; 
 int /*<<< orphan*/  CDCORE_DEFAULT ; 
 int /*<<< orphan*/  M68KCORE_C68K ; 
 int /*<<< orphan*/  OSDCORE_DEFAULT ; 
 int /*<<< orphan*/  PERCORE_GTK ; 
 int /*<<< orphan*/  SH2CORE_DEFAULT ; 
 int /*<<< orphan*/  SNDCORE_DUMMY ; 
 int /*<<< orphan*/  VIDCORE_OGL ; 
 int /*<<< orphan*/  VIDCORE_SOFT ; 
 int /*<<< orphan*/  VIDEOFORMATTYPE_NTSC ; 
 int /*<<< orphan*/  biospath ; 
 int /*<<< orphan*/  buppath ; 
 int /*<<< orphan*/  cartpath ; 
 int /*<<< orphan*/  cdpath ; 
 int /*<<< orphan*/  mpegpath ; 
 TYPE_1__ yinit ; 

__attribute__((used)) static void yui_settings_init(void) {
	yinit.m68kcoretype = M68KCORE_C68K;
	yinit.percoretype = PERCORE_GTK;
	yinit.sh2coretype = SH2CORE_DEFAULT;
#ifdef HAVE_LIBGTKGLEXT
	yinit.vidcoretype = VIDCORE_OGL;
#else
	yinit.vidcoretype = VIDCORE_SOFT;
#endif
	yinit.sndcoretype = SNDCORE_DUMMY;
	yinit.cdcoretype = CDCORE_DEFAULT;
	yinit.carttype = CART_NONE;
	yinit.regionid = 0;
	yinit.biospath = biospath;
	yinit.cdpath = cdpath;
	yinit.buppath = buppath;
	yinit.mpegpath = mpegpath;
	yinit.cartpath = cartpath;
        yinit.videoformattype = VIDEOFORMATTYPE_NTSC;
	yinit.osdcoretype = OSDCORE_DEFAULT;
	yinit.skip_load = 0;
}