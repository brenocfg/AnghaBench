#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int type; int /*<<< orphan*/  gain; int /*<<< orphan*/  width; int /*<<< orphan*/  freq; } ;
typedef  TYPE_1__ EqualizatorFilter ;

/* Variables and functions */
#define  BUTTERWORTH 130 
#define  CHEBYSHEV1 129 
#define  CHEBYSHEV2 128 
 int /*<<< orphan*/  FILTER_ORDER ; 
 int /*<<< orphan*/  butterworth_bp_filter (TYPE_1__*,int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 double butterworth_compute_bw_gain_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chebyshev1_bp_filter (TYPE_1__*,int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 double chebyshev1_compute_bw_gain_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chebyshev2_bp_filter (TYPE_1__*,int /*<<< orphan*/ ,double,double,int /*<<< orphan*/ ,double,int /*<<< orphan*/ ) ; 
 double chebyshev2_compute_bw_gain_db (int /*<<< orphan*/ ) ; 
 double hz_2_rad (int /*<<< orphan*/ ,double) ; 

__attribute__((used)) static void equalizer(EqualizatorFilter *f, double sample_rate)
{
    double w0 = hz_2_rad(f->freq,  sample_rate);
    double wb = hz_2_rad(f->width, sample_rate);
    double bw_gain;

    switch (f->type) {
    case BUTTERWORTH:
        bw_gain = butterworth_compute_bw_gain_db(f->gain);
        butterworth_bp_filter(f, FILTER_ORDER, w0, wb, f->gain, bw_gain, 0);
        break;
    case CHEBYSHEV1:
        bw_gain = chebyshev1_compute_bw_gain_db(f->gain);
        chebyshev1_bp_filter(f, FILTER_ORDER, w0, wb, f->gain, bw_gain, 0);
        break;
    case CHEBYSHEV2:
        bw_gain = chebyshev2_compute_bw_gain_db(f->gain);
        chebyshev2_bp_filter(f, FILTER_ORDER, w0, wb, f->gain, bw_gain, 0);
        break;
    }

}