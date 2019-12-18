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
struct TYPE_3__ {int js_subband_start; } ;
typedef  TYPE_1__ COOKSubpacket ;
typedef  int /*<<< orphan*/  COOKContext ;

/* Variables and functions */
 int SUBBAND_SIZE ; 

__attribute__((used)) static void decouple_float(COOKContext *q,
                           COOKSubpacket *p,
                           int subband,
                           float f1, float f2,
                           float *decode_buffer,
                           float *mlt_buffer1, float *mlt_buffer2)
{
    int j, tmp_idx;
    for (j = 0; j < SUBBAND_SIZE; j++) {
        tmp_idx = ((p->js_subband_start + subband) * SUBBAND_SIZE) + j;
        mlt_buffer1[SUBBAND_SIZE * subband + j] = f1 * decode_buffer[tmp_idx];
        mlt_buffer2[SUBBAND_SIZE * subband + j] = f2 * decode_buffer[tmp_idx];
    }
}