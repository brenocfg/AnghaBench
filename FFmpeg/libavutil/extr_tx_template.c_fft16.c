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
typedef  int /*<<< orphan*/  FFTSample ;
typedef  int /*<<< orphan*/  FFTComplex ;

/* Variables and functions */
 int /*<<< orphan*/  M_SQRT1_2 ; 
 int /*<<< orphan*/  TRANSFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSFORM_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * TX_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_cos_16 ; 
 int /*<<< orphan*/  fft4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fft8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fft16(FFTComplex *z)
{
    FFTSample t1, t2, t3, t4, t5, t6;
    FFTSample cos_16_1 = TX_NAME(ff_cos_16)[1];
    FFTSample cos_16_3 = TX_NAME(ff_cos_16)[3];

    fft8(z);
    fft4(z+8);
    fft4(z+12);

    TRANSFORM_ZERO(z[0],z[4],z[8],z[12]);
    TRANSFORM(z[2],z[6],z[10],z[14],M_SQRT1_2,M_SQRT1_2);
    TRANSFORM(z[1],z[5],z[9],z[13],cos_16_1,cos_16_3);
    TRANSFORM(z[3],z[7],z[11],z[15],cos_16_3,cos_16_1);
}