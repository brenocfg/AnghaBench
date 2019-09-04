#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_mstr_exp; int* exponents; } ;
struct TYPE_8__ {int /*<<< orphan*/  gb; } ;
struct TYPE_7__ {int nb_exponent; int* nb_bias_exp; int exp_ofs; } ;
typedef  TYPE_1__ DBEGroup ;
typedef  TYPE_2__ DBEContext ;
typedef  TYPE_3__ DBEChannel ;

/* Variables and functions */
 int MAX_BIAS_EXP ; 
 int MAX_MSTR_EXP ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void unbias_exponents(DBEContext *s, DBEChannel *c, DBEGroup *g)
{
    int mstr_exp[MAX_MSTR_EXP];
    int bias_exp[MAX_BIAS_EXP];
    int i, j, k;

    for (i = 0; i < c->nb_mstr_exp; i++)
        mstr_exp[i] = get_bits(&s->gb, 2) * 6;

    for (i = 0; i < g->nb_exponent; i++)
        bias_exp[i] = get_bits(&s->gb, 5);

    for (i = k = 0; i < c->nb_mstr_exp; i++)
        for (j = 0; j < g->nb_bias_exp[i]; j++, k++)
            c->exponents[g->exp_ofs + k] = mstr_exp[i] + bias_exp[k];
}