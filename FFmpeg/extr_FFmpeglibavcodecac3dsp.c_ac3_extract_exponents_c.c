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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int abs (int /*<<< orphan*/ ) ; 
 int av_log2 (int) ; 

__attribute__((used)) static void ac3_extract_exponents_c(uint8_t *exp, int32_t *coef, int nb_coefs)
{
    int i;

    for (i = 0; i < nb_coefs; i++) {
        int v = abs(coef[i]);
        exp[i] = v ? 23 - av_log2(v) : 24;
    }
}