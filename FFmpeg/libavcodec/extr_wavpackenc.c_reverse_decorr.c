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
struct Decorr {int value; int* samplesA; int* samplesB; } ;
typedef  void* int32_t ;

/* Variables and functions */
 int MAX_TERM ; 

__attribute__((used)) static void reverse_decorr(struct Decorr *dpp)
{
    if (dpp->value > MAX_TERM) {
        int32_t sam_A, sam_B;

        if (dpp->value & 1) {
            sam_A = 2 * dpp->samplesA[0] - dpp->samplesA[1];
            sam_B = 2 * dpp->samplesB[0] - dpp->samplesB[1];
        } else {
            sam_A = (3 * dpp->samplesA[0] - dpp->samplesA[1]) >> 1;
            sam_B = (3 * dpp->samplesB[0] - dpp->samplesB[1]) >> 1;
        }

        dpp->samplesA[1] = dpp->samplesA[0];
        dpp->samplesB[1] = dpp->samplesB[0];
        dpp->samplesA[0] = sam_A;
        dpp->samplesB[0] = sam_B;

        if (dpp->value & 1) {
            sam_A = 2 * dpp->samplesA[0] - dpp->samplesA[1];
            sam_B = 2 * dpp->samplesB[0] - dpp->samplesB[1];
        } else {
            sam_A = (3 * dpp->samplesA[0] - dpp->samplesA[1]) >> 1;
            sam_B = (3 * dpp->samplesB[0] - dpp->samplesB[1]) >> 1;
        }

        dpp->samplesA[1] = sam_A;
        dpp->samplesB[1] = sam_B;
    } else if (dpp->value > 1) {
        int i, j, k;

        for (i = 0, j = dpp->value - 1, k = 0; k < dpp->value / 2; i++, j--, k++) {
            i &= (MAX_TERM - 1);
            j &= (MAX_TERM - 1);
            dpp->samplesA[i] ^= dpp->samplesA[j];
            dpp->samplesA[j] ^= dpp->samplesA[i];
            dpp->samplesA[i] ^= dpp->samplesA[j];
            dpp->samplesB[i] ^= dpp->samplesB[j];
            dpp->samplesB[j] ^= dpp->samplesB[i];
            dpp->samplesB[i] ^= dpp->samplesB[j];
        }
    }
}