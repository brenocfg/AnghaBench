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

/* Variables and functions */

__attribute__((used)) static void inv_predict_8(uint8_t *p, const uint8_t *p_l, const uint8_t *p_tl,
                          const uint8_t *p_t, const uint8_t *p_tr)
{
    p[0] = p_tl[0] + p_t[0] >> 1;
    p[1] = p_tl[1] + p_t[1] >> 1;
    p[2] = p_tl[2] + p_t[2] >> 1;
    p[3] = p_tl[3] + p_t[3] >> 1;
}