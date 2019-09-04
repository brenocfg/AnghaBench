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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_COPY32 (scalar_t__*,scalar_t__ const*) ; 
 int FFABS (scalar_t__ const) ; 

__attribute__((used)) static void inv_predict_11(uint8_t *p, const uint8_t *p_l, const uint8_t *p_tl,
                           const uint8_t *p_t, const uint8_t *p_tr)
{
    int diff = (FFABS(p_l[0] - p_tl[0]) - FFABS(p_t[0] - p_tl[0])) +
               (FFABS(p_l[1] - p_tl[1]) - FFABS(p_t[1] - p_tl[1])) +
               (FFABS(p_l[2] - p_tl[2]) - FFABS(p_t[2] - p_tl[2])) +
               (FFABS(p_l[3] - p_tl[3]) - FFABS(p_t[3] - p_tl[3]));
    if (diff <= 0)
        AV_COPY32(p, p_t);
    else
        AV_COPY32(p, p_l);
}