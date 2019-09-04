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
typedef  enum TAKFrameSizeType { ____Placeholder_TAKFrameSizeType } TAKFrameSizeType ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FF_ARRAY_ELEMS (int*) ; 
 int TAK_FRAME_DURATION_QUANT_SHIFT ; 
 int TAK_FST_250ms ; 
 int* frame_duration_type_quants ; 

__attribute__((used)) static int tak_get_nb_samples(int sample_rate, enum TAKFrameSizeType type)
{
    int nb_samples, max_nb_samples;

    if (type <= TAK_FST_250ms) {
        nb_samples     = sample_rate * frame_duration_type_quants[type] >>
                         TAK_FRAME_DURATION_QUANT_SHIFT;
        max_nb_samples = 16384;
    } else if (type < FF_ARRAY_ELEMS(frame_duration_type_quants)) {
        nb_samples     = frame_duration_type_quants[type];
        max_nb_samples = sample_rate *
                         frame_duration_type_quants[TAK_FST_250ms] >>
                         TAK_FRAME_DURATION_QUANT_SHIFT;
    } else {
        return AVERROR_INVALIDDATA;
    }

    if (nb_samples <= 0 || nb_samples > max_nb_samples)
        return AVERROR_INVALIDDATA;

    return nb_samples;
}