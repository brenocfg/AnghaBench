#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ws_intervals {int nb_inter; TYPE_1__* inter; } ;
struct sbg_script {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * extradata; } ;
struct TYPE_5__ {int type; int channels; int f1; int f2; int a1; int a2; int phi; int /*<<< orphan*/  ts2; int /*<<< orphan*/  ts1; } ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_EDATA32 (int) ; 
 int /*<<< orphan*/  ADD_EDATA64 (int /*<<< orphan*/ ) ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  WS_NOISE 129 
#define  WS_SINE 128 
 scalar_t__ ff_alloc_extradata (TYPE_2__*,int) ; 

__attribute__((used)) static int encode_intervals(struct sbg_script *s, AVCodecParameters *par,
                            struct ws_intervals *inter)
{
    int i, edata_size = 4;
    uint8_t *edata;

    for (i = 0; i < inter->nb_inter; i++) {
        edata_size += inter->inter[i].type == WS_SINE  ? 44 :
                      inter->inter[i].type == WS_NOISE ? 32 : 0;
        if (edata_size < 0)
            return AVERROR(ENOMEM);
    }
    if (ff_alloc_extradata(par, edata_size))
        return AVERROR(ENOMEM);
    edata = par->extradata;

#define ADD_EDATA32(v) do { AV_WL32(edata, (v)); edata += 4; } while(0)
#define ADD_EDATA64(v) do { AV_WL64(edata, (v)); edata += 8; } while(0)
    ADD_EDATA32(inter->nb_inter);
    for (i = 0; i < inter->nb_inter; i++) {
        ADD_EDATA64(inter->inter[i].ts1);
        ADD_EDATA64(inter->inter[i].ts2);
        ADD_EDATA32(inter->inter[i].type);
        ADD_EDATA32(inter->inter[i].channels);
        switch (inter->inter[i].type) {
            case WS_SINE:
                ADD_EDATA32(inter->inter[i].f1);
                ADD_EDATA32(inter->inter[i].f2);
                ADD_EDATA32(inter->inter[i].a1);
                ADD_EDATA32(inter->inter[i].a2);
                ADD_EDATA32(inter->inter[i].phi);
                break;
            case WS_NOISE:
                ADD_EDATA32(inter->inter[i].a1);
                ADD_EDATA32(inter->inter[i].a2);
                break;
        }
    }
    if (edata != par->extradata + edata_size)
        return AVERROR_BUG;
    return 0;
}