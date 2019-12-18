#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nb_groups; float* mantissas; int* bap; int* idx; size_t* exponents; int bw_code; TYPE_1__* groups; } ;
struct TYPE_7__ {int /*<<< orphan*/  gb; } ;
struct TYPE_6__ {int mnt_ofs; int nb_exponent; int exp_ofs; int* nb_mantissa; } ;
typedef  TYPE_1__ DBEGroup ;
typedef  TYPE_2__ DBEContext ;
typedef  TYPE_3__ DBEChannel ;

/* Variables and functions */
 float* exponent_tab ; 
 float get_sbits (int /*<<< orphan*/ *,int) ; 
 int** mantissa_size1 ; 
 int** mantissa_size2 ; 
 float** mantissa_tab1 ; 
 float** mantissa_tab2 ; 
 float** mantissa_tab3 ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int parse_mantissas(DBEContext *s, DBEChannel *c)
{
    DBEGroup *g;
    int i, j, k;

    for (i = 0, g = c->groups; i < c->nb_groups; i++, g++) {
        float *mnt = c->mantissas + g->mnt_ofs;

        for (j = 0; j < g->nb_exponent; j++) {
            int bap     = c->bap[g->exp_ofs + j];
            int idx     = c->idx[g->exp_ofs + j];
            int size1   = mantissa_size1[bap][idx];
            int count   = g->nb_mantissa[j];
            float exp   = exponent_tab[c->exponents[g->exp_ofs + j]];
            float scale = mantissa_tab1[size1][idx] * exp;

            if (!size1) {
                memset(mnt, 0, count * sizeof(*mnt));
            } else if (idx) {
                int values[100];
                int escape = -(1 << size1 - 1);

                for (k = 0; k < count; k++)
                    values[k] = get_sbits(&s->gb, size1);

                for (k = 0; k < count; k++) {
                    if (values[k] != escape) {
                        mnt[k] = values[k] * scale;
                    } else {
                        int size2 = mantissa_size2[bap][idx];
                        int value = get_sbits(&s->gb, size2);
                        float a = mantissa_tab2[size2][idx];
                        float b = mantissa_tab3[size2][idx];
                        if (value < 0)
                            mnt[k] = ((value + 1) * a - b) * exp;
                        else
                            mnt[k] = (value * a + b) * exp;
                    }
                }
            } else {
                for (k = 0; k < count; k++)
                    mnt[k] = get_sbits(&s->gb, size1) * scale;
            }

            mnt += count;
        }

        for (; j < g->nb_exponent + c->bw_code; j++) {
            memset(mnt, 0, g->nb_mantissa[j] * sizeof(*mnt));
            mnt += g->nb_mantissa[j];
        }
    }

    return 0;
}