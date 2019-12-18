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
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;

/* Variables and functions */
#define  AVCOL_SPC_BT470BG 134 
#define  AVCOL_SPC_BT709 133 
#define  AVCOL_SPC_FCC 132 
#define  AVCOL_SPC_RGB 131 
#define  AVCOL_SPC_SMPTE170M 130 
#define  AVCOL_SPC_SMPTE240M 129 
#define  AVCOL_SPC_YCOCG 128 
 unsigned int FF_ARRAY_ELEMS (char const* const*) ; 

const char *av_get_colorspace_name(enum AVColorSpace val)
{
    static const char * const name[] = {
        [AVCOL_SPC_RGB]       = "GBR",
        [AVCOL_SPC_BT709]     = "bt709",
        [AVCOL_SPC_FCC]       = "fcc",
        [AVCOL_SPC_BT470BG]   = "bt470bg",
        [AVCOL_SPC_SMPTE170M] = "smpte170m",
        [AVCOL_SPC_SMPTE240M] = "smpte240m",
        [AVCOL_SPC_YCOCG]     = "YCgCo",
    };
    if ((unsigned)val >= FF_ARRAY_ELEMS(name))
        return NULL;
    return name[val];
}