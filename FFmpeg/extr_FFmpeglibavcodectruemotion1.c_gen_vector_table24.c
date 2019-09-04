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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int* y_predictor_table; int* c_predictor_table; int* fat_y_predictor_table; int* fat_c_predictor_table; int /*<<< orphan*/  fat_cdt; int /*<<< orphan*/  fat_ydt; int /*<<< orphan*/  cdt; int /*<<< orphan*/  ydt; } ;
typedef  TYPE_1__ TrueMotion1Context ;

/* Variables and functions */
 int make_cdt24_entry (unsigned char,unsigned char,int /*<<< orphan*/ ) ; 
 int make_ydt24_entry (unsigned char,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen_vector_table24(TrueMotion1Context *s, const uint8_t *sel_vector_table)
{
    int len, i, j;
    unsigned char delta_pair;

    for (i = 0; i < 1024; i += 4)
    {
        len = *sel_vector_table++ / 2;
        for (j = 0; j < len; j++)
        {
            delta_pair = *sel_vector_table++;
            s->y_predictor_table[i+j] = 0xfffffffe &
                make_ydt24_entry(delta_pair >> 4, delta_pair & 0xf, s->ydt);
            s->c_predictor_table[i+j] = 0xfffffffe &
                make_cdt24_entry(delta_pair >> 4, delta_pair & 0xf, s->cdt);
            s->fat_y_predictor_table[i+j] = 0xfffffffe &
                make_ydt24_entry(delta_pair >> 4, delta_pair & 0xf, s->fat_ydt);
            s->fat_c_predictor_table[i+j] = 0xfffffffe &
                make_cdt24_entry(delta_pair >> 4, delta_pair & 0xf, s->fat_cdt);
        }
        s->y_predictor_table[i+(j-1)] |= 1;
        s->c_predictor_table[i+(j-1)] |= 1;
        s->fat_y_predictor_table[i+(j-1)] |= 1;
        s->fat_c_predictor_table[i+(j-1)] |= 1;
    }
}