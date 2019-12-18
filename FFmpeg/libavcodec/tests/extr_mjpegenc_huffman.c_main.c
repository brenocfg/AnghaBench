#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int code; int length; } ;
struct TYPE_10__ {int value; int prob; } ;
typedef  TYPE_1__ PTable ;
typedef  TYPE_2__ HuffTable ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_2__*) ; 
 scalar_t__ check_lengths (int,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ff_mjpegenc_huffman_compute_bits (TYPE_1__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_2__* probs_sat ; 
 TYPE_2__* probs_skewed ; 
 TYPE_2__* probs_zeroes ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
    int i, ret = 0;
    // Probabilities of symbols 0..4
    PTable val_counts[] = {
        {.value = 0, .prob = 1},
        {.value = 1, .prob = 2},
        {.value = 2, .prob = 5},
        {.value = 3, .prob = 10},
        {.value = 4, .prob = 21},
    };
    // Expected code lengths for each symbol
    static const HuffTable expected[] = {
        {.code = 0, .length = 3},
        {.code = 1, .length = 3},
        {.code = 2, .length = 3},
        {.code = 3, .length = 3},
        {.code = 4, .length = 1},
    };
    // Actual code lengths
    HuffTable distincts[5];

    // Build optimal huffman tree using an internal function, to allow for
    // smaller-than-normal test cases. This mutates val_counts by sorting.
    ff_mjpegenc_huffman_compute_bits(val_counts, distincts,
                                     FF_ARRAY_ELEMS(distincts), 3);

    for (i = 0; i < FF_ARRAY_ELEMS(distincts); i++) {
        if (distincts[i].code != expected[i].code ||
            distincts[i].length != expected[i].length) {
            fprintf(stderr,
                    "Built huffman does not equal expectations. "
                    "Expected: code %d probability %d, "
                    "Actual: code %d probability %d\n",
                    expected[i].code, expected[i].length,
                    distincts[i].code, distincts[i].length);
            ret = 1;
        }
    }

    // Check handling of zero probabilities
    if (check_lengths(16, 18, probs_zeroes, FF_ARRAY_ELEMS(probs_zeroes)))
        ret = 1;
    // Check skewed distribution over 256 without saturated lengths
    if (check_lengths(16, 41282, probs_skewed, FF_ARRAY_ELEMS(probs_skewed)))
        ret = 1;
    // Check skewed distribution over 256 with saturated lengths
    if (check_lengths(16, 669904, probs_sat, FF_ARRAY_ELEMS(probs_sat)))
        ret = 1;

    return ret;
}