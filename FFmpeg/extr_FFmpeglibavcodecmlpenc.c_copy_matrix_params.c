#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * outch; int /*<<< orphan*/ ** coeff; int /*<<< orphan*/ * shift; int /*<<< orphan*/ * fbits; scalar_t__ count; } ;
typedef  TYPE_1__ MatrixParams ;

/* Variables and functions */
 unsigned int MAX_CHANNELS ; 
 unsigned int MAX_MATRICES ; 

__attribute__((used)) static void copy_matrix_params(MatrixParams *dst, MatrixParams *src)
{
    dst->count = src->count;

    if (dst->count) {
        unsigned int channel, count;

        for (channel = 0; channel < MAX_CHANNELS; channel++) {

            dst->fbits[channel] = src->fbits[channel];
            dst->shift[channel] = src->shift[channel];

            for (count = 0; count < MAX_MATRICES; count++)
                dst->coeff[count][channel] = src->coeff[count][channel];
        }

        for (count = 0; count < MAX_MATRICES; count++)
            dst->outch[count] = src->outch[count];
    }
}