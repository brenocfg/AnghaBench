#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int csp; double** cmatrix; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ShowCQTContext ;

/* Variables and functions */
#define  AVCOL_SPC_BT2020_NCL 134 
#define  AVCOL_SPC_BT470BG 133 
#define  AVCOL_SPC_BT709 132 
#define  AVCOL_SPC_FCC 131 
#define  AVCOL_SPC_SMPTE170M 130 
#define  AVCOL_SPC_SMPTE240M 129 
#define  AVCOL_SPC_UNSPECIFIED 128 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void init_colormatrix(ShowCQTContext *s)
{
    double kr, kg, kb;

    /* from vf_colorspace.c */
    switch (s->csp) {
    default:
        av_log(s->ctx, AV_LOG_WARNING, "unsupported colorspace, setting it to unspecified.\n");
        s->csp = AVCOL_SPC_UNSPECIFIED;
    case AVCOL_SPC_UNSPECIFIED:
    case AVCOL_SPC_BT470BG:
    case AVCOL_SPC_SMPTE170M:
        kr = 0.299; kb = 0.114; break;
    case AVCOL_SPC_BT709:
        kr = 0.2126; kb = 0.0722; break;
    case AVCOL_SPC_FCC:
        kr = 0.30; kb = 0.11; break;
    case AVCOL_SPC_SMPTE240M:
        kr = 0.212; kb = 0.087; break;
    case AVCOL_SPC_BT2020_NCL:
        kr = 0.2627; kb = 0.0593; break;
    }

    kg = 1.0 - kr - kb;
    s->cmatrix[0][0] = 219.0 * kr;
    s->cmatrix[0][1] = 219.0 * kg;
    s->cmatrix[0][2] = 219.0 * kb;
    s->cmatrix[1][0] = -112.0 * kr / (1.0 - kb);
    s->cmatrix[1][1] = -112.0 * kg / (1.0 - kb);
    s->cmatrix[1][2] = 112.0;
    s->cmatrix[2][0] = 112.0;
    s->cmatrix[2][1] = -112.0 * kg / (1.0 - kr);
    s->cmatrix[2][2] = -112.0 * kb / (1.0 - kr);
}