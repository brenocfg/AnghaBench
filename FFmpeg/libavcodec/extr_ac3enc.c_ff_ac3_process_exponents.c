#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AC3EncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  compute_exp_strategy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  encode_exponents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extract_exponents (int /*<<< orphan*/ *) ; 

void ff_ac3_process_exponents(AC3EncodeContext *s)
{
    extract_exponents(s);

    compute_exp_strategy(s);

    encode_exponents(s);

    emms_c();
}