#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int instance_number; scalar_t__ umid; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB64 (scalar_t__,int) ; 
 int av_get_random_seed () ; 

__attribute__((used)) static void mxf_gen_umid(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    uint32_t seed = av_get_random_seed();
    uint64_t umid = seed + 0x5294713400000000LL;

    AV_WB64(mxf->umid  , umid);
    AV_WB64(mxf->umid+8, umid>>8);

    mxf->instance_number = seed & 0xFFFFFF;
}