#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_7__ {int /*<<< orphan*/  gb; scalar_t__** block; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* rv34_idct_dc_add ) (int /*<<< orphan*/ *,int,scalar_t__) ;int /*<<< orphan*/  (* rv34_idct_add ) (int /*<<< orphan*/ *,int,scalar_t__*) ;} ;
struct TYPE_6__ {TYPE_1__ rdsp; int /*<<< orphan*/  cur_vlcs; TYPE_3__ s; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int rv34_decode_block (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static inline void rv34_process_block(RV34DecContext *r,
                                      uint8_t *pdst, int stride,
                                      int fc, int sc, int q_dc, int q_ac)
{
    MpegEncContext *s = &r->s;
    int16_t *ptr = s->block[0];
    int has_ac = rv34_decode_block(ptr, &s->gb, r->cur_vlcs,
                                   fc, sc, q_dc, q_ac, q_ac);
    if(has_ac){
        r->rdsp.rv34_idct_add(pdst, stride, ptr);
    }else{
        r->rdsp.rv34_idct_dc_add(pdst, stride, ptr[0]);
        ptr[0] = 0;
    }
}