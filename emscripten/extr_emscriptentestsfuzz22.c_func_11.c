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
typedef  int uint32_t ;
typedef  unsigned long uint16_t ;
typedef  unsigned long int8_t ;

/* Variables and functions */
 unsigned long*** g_14 ; 
 int* g_17 ; 
 int g_18 ; 

__attribute__((used)) static int8_t  func_11(uint32_t  p_12)
{ /* block id: 2 */
    uint16_t l_19 = 0UL;
    for (p_12 = 0; p_12 < 3; p_12 += 1)
    {
        for (g_17[3] = 0; g_17[3] < 3; g_17[3] += 1)
        {
            for (g_18 = 0; g_18 < 1; g_18 += 1)
            {
                g_14[p_12][g_17[3]][g_18] = 7UL;
            }
        }
    }
    return l_19;
}