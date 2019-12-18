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
struct TYPE_3__ {int nb_nans; int nb_infs; int nb_denormals; } ;
typedef  TYPE_1__ ChannelStats ;
typedef  int /*<<< orphan*/  AudioStatsContext ;

/* Variables and functions */
 int FP_INFINITE ; 
 int FP_NAN ; 
 int FP_SUBNORMAL ; 
 int fpclassify (float) ; 

__attribute__((used)) static inline void update_float_stat(AudioStatsContext *s, ChannelStats *p, float d)
{
    int type = fpclassify(d);

    p->nb_nans      += type == FP_NAN;
    p->nb_infs      += type == FP_INFINITE;
    p->nb_denormals += type == FP_SUBNORMAL;
}