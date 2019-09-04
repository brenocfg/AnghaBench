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
struct TYPE_5__ {TYPE_1__* prob; } ;
typedef  TYPE_2__ VP8Context ;
struct TYPE_4__ {int /*<<< orphan*/ ** token; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t* vp8_coeff_band ; 
 int /*<<< orphan*/ ** vp8_token_default_probs ; 

__attribute__((used)) static void vp78_reset_probability_tables(VP8Context *s)
{
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 16; j++)
            memcpy(s->prob->token[i][j], vp8_token_default_probs[i][vp8_coeff_band[j]],
                   sizeof(s->prob->token[i][j]));
}