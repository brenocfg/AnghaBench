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
typedef  int uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_3__ {int mant1_cnt; int* qmant1_ptr; int mant2_cnt; int* qmant2_ptr; int mant4_cnt; int* qmant4_ptr; } ;
typedef  TYPE_1__ AC3Mant ;

/* Variables and functions */
 int asym_quant (int,int,int) ; 
 int sym_quant (int,int,int) ; 

__attribute__((used)) static void quantize_mantissas_blk_ch(AC3Mant *s, int32_t *fixed_coef,
                                      uint8_t *exp, uint8_t *bap,
                                      int16_t *qmant, int start_freq,
                                      int end_freq)
{
    int i;

    for (i = start_freq; i < end_freq; i++) {
        int c = fixed_coef[i];
        int e = exp[i];
        int v = bap[i];
        if (v)
        switch (v) {
        case 1:
            v = sym_quant(c, e, 3);
            switch (s->mant1_cnt) {
            case 0:
                s->qmant1_ptr = &qmant[i];
                v = 9 * v;
                s->mant1_cnt = 1;
                break;
            case 1:
                *s->qmant1_ptr += 3 * v;
                s->mant1_cnt = 2;
                v = 128;
                break;
            default:
                *s->qmant1_ptr += v;
                s->mant1_cnt = 0;
                v = 128;
                break;
            }
            break;
        case 2:
            v = sym_quant(c, e, 5);
            switch (s->mant2_cnt) {
            case 0:
                s->qmant2_ptr = &qmant[i];
                v = 25 * v;
                s->mant2_cnt = 1;
                break;
            case 1:
                *s->qmant2_ptr += 5 * v;
                s->mant2_cnt = 2;
                v = 128;
                break;
            default:
                *s->qmant2_ptr += v;
                s->mant2_cnt = 0;
                v = 128;
                break;
            }
            break;
        case 3:
            v = sym_quant(c, e, 7);
            break;
        case 4:
            v = sym_quant(c, e, 11);
            switch (s->mant4_cnt) {
            case 0:
                s->qmant4_ptr = &qmant[i];
                v = 11 * v;
                s->mant4_cnt = 1;
                break;
            default:
                *s->qmant4_ptr += v;
                s->mant4_cnt = 0;
                v = 128;
                break;
            }
            break;
        case 5:
            v = sym_quant(c, e, 15);
            break;
        case 14:
            v = asym_quant(c, e, 14);
            break;
        case 15:
            v = asym_quant(c, e, 16);
            break;
        default:
            v = asym_quant(c, e, v - 1);
            break;
        }
        qmant[i] = v;
    }
}