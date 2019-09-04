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
 int AVCOL_SPC_BT2020_NCL ; 
 int AVCOL_SPC_BT470BG ; 
 int AVCOL_SPC_BT709 ; 
 int AVCOL_SPC_FCC ; 
 int AVCOL_SPC_SMPTE240M ; 
 scalar_t__ strstr (char const*,char*) ; 
 int const* sws_getCoefficients (int) ; 

__attribute__((used)) static const int *parse_yuv_type(const char *s, enum AVColorSpace colorspace)
{
    if (!s)
        s = "bt601";

    if (s && strstr(s, "bt709")) {
        colorspace = AVCOL_SPC_BT709;
    } else if (s && strstr(s, "fcc")) {
        colorspace = AVCOL_SPC_FCC;
    } else if (s && strstr(s, "smpte240m")) {
        colorspace = AVCOL_SPC_SMPTE240M;
    } else if (s && (strstr(s, "bt601") || strstr(s, "bt470") || strstr(s, "smpte170m"))) {
        colorspace = AVCOL_SPC_BT470BG;
    } else if (s && strstr(s, "bt2020")) {
        colorspace = AVCOL_SPC_BT2020_NCL;
    }

    if (colorspace < 1 || colorspace > 10 || colorspace == 8) {
        colorspace = AVCOL_SPC_BT470BG;
    }

    return sws_getCoefficients(colorspace);
}