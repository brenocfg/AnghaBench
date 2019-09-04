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
typedef  int uint8_t ;
struct TYPE_4__ {int range; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ CABACContext ;

/* Variables and functions */
 int* ff_h264_lps_range ; 
 int* ff_h264_mlps_state ; 
 int /*<<< orphan*/  renorm_cabac_encoder (TYPE_1__*) ; 

__attribute__((used)) static void put_cabac(CABACContext *c, uint8_t * const state, int bit){
    int RangeLPS= ff_h264_lps_range[2*(c->range&0xC0) + *state];

    if(bit == ((*state)&1)){
        c->range -= RangeLPS;
        *state    = ff_h264_mlps_state[128 + *state];
    }else{
        c->low += c->range - RangeLPS;
        c->range = RangeLPS;
        *state= ff_h264_mlps_state[127 - *state];
    }

    renorm_cabac_encoder(c);
}