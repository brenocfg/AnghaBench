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
typedef  int int8_t ;
struct TYPE_4__ {size_t qscale; int /*<<< orphan*/  gb; scalar_t__ modified_quant; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 size_t** ff_modified_quant_tab ; 
 int /*<<< orphan*/  ff_set_qscale (TYPE_1__*,size_t) ; 
 size_t get_bits (int /*<<< orphan*/ *,int) ; 
 size_t get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h263_decode_dquant(MpegEncContext *s){
    static const int8_t quant_tab[4] = { -1, -2, 1, 2 };

    if(s->modified_quant){
        if(get_bits1(&s->gb))
            s->qscale= ff_modified_quant_tab[get_bits1(&s->gb)][ s->qscale ];
        else
            s->qscale= get_bits(&s->gb, 5);
    }else
        s->qscale += quant_tab[get_bits(&s->gb, 2)];
    ff_set_qscale(s, s->qscale);
}