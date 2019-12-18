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
struct TYPE_3__ {int /*<<< orphan*/  gb; void* coef0_pos; } ;
typedef  TYPE_1__ IMCContext ;

/* Variables and functions */
 int BANDS ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void imc_read_level_coeffs_raw(IMCContext *q, int stream_format_code,
                                      int *levlCoeffs)
{
    int i;

    q->coef0_pos  = get_bits(&q->gb, 5);
    levlCoeffs[0] = get_bits(&q->gb, 7);
    for (i = 1; i < BANDS; i++)
        levlCoeffs[i] = get_bits(&q->gb, 4);
}