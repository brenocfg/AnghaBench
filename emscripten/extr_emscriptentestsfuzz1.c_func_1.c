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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/ * func_9 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_4 ; 
 int /*<<< orphan*/  g_5 ; 
 int /*<<< orphan*/ *** g_7 ; 
 scalar_t__ safe_unary_minus_func_int16_t_s (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t  func_1(void)
{ /* block id: 0 */
    int32_t l_3 = (-1L);
    if (((safe_unary_minus_func_int16_t_s(l_3)) >= g_4))
    { /* block id: 1 */
        int32_t *l_8 = &l_3;
        g_5 = g_5;
        (*l_8) ^= (g_7[1][3][2] , 0x44688D23L);
    }
    else
    { /* block id: 4 */
        int32_t *l_12 = &l_3;
        int32_t **l_13 = &l_12;
        (*l_13) = func_9(((*l_13) = l_12), l_3);
    }
    return l_3;
}