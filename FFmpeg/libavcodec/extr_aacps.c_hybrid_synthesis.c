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
typedef  int /*<<< orphan*/  out ;
typedef  scalar_t__ UINTFLOAT ;
struct TYPE_3__ {int /*<<< orphan*/  (* hybrid_synthesis_deint ) (scalar_t__***,scalar_t__***,int,int) ;} ;
typedef  TYPE_1__ PSDSPContext ;
typedef  scalar_t__ INTFLOAT ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__***,scalar_t__***,int,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__***,scalar_t__***,int,int) ; 

__attribute__((used)) static void hybrid_synthesis(PSDSPContext *dsp, INTFLOAT out[2][38][64],
                             INTFLOAT in[91][32][2], int is34, int len)
{
    int i, n;
    if (is34) {
        for (n = 0; n < len; n++) {
            memset(out[0][n], 0, 5*sizeof(out[0][n][0]));
            memset(out[1][n], 0, 5*sizeof(out[1][n][0]));
            for (i = 0; i < 12; i++) {
                out[0][n][0] += (UINTFLOAT)in[   i][n][0];
                out[1][n][0] += (UINTFLOAT)in[   i][n][1];
            }
            for (i = 0; i < 8; i++) {
                out[0][n][1] += (UINTFLOAT)in[12+i][n][0];
                out[1][n][1] += (UINTFLOAT)in[12+i][n][1];
            }
            for (i = 0; i < 4; i++) {
                out[0][n][2] += (UINTFLOAT)in[20+i][n][0];
                out[1][n][2] += (UINTFLOAT)in[20+i][n][1];
                out[0][n][3] += (UINTFLOAT)in[24+i][n][0];
                out[1][n][3] += (UINTFLOAT)in[24+i][n][1];
                out[0][n][4] += (UINTFLOAT)in[28+i][n][0];
                out[1][n][4] += (UINTFLOAT)in[28+i][n][1];
            }
        }
        dsp->hybrid_synthesis_deint(out, in + 27, 5, len);
    } else {
        for (n = 0; n < len; n++) {
            out[0][n][0] = (UINTFLOAT)in[0][n][0] + in[1][n][0] + in[2][n][0] +
                           (UINTFLOAT)in[3][n][0] + in[4][n][0] + in[5][n][0];
            out[1][n][0] = (UINTFLOAT)in[0][n][1] + in[1][n][1] + in[2][n][1] +
                           (UINTFLOAT)in[3][n][1] + in[4][n][1] + in[5][n][1];
            out[0][n][1] = (UINTFLOAT)in[6][n][0] + in[7][n][0];
            out[1][n][1] = (UINTFLOAT)in[6][n][1] + in[7][n][1];
            out[0][n][2] = (UINTFLOAT)in[8][n][0] + in[9][n][0];
            out[1][n][2] = (UINTFLOAT)in[8][n][1] + in[9][n][1];
        }
        dsp->hybrid_synthesis_deint(out, in + 7, 3, len);
    }
}