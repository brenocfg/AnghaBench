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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int g_36 ; 
 unsigned long* g_40 ; 
 int g_46 ; 
 int*** g_51 ; 
 int g_52 ; 

__attribute__((used)) static uint32_t * func_22(int16_t  p_23, uint32_t  p_24, uint32_t * p_25)
{ /* block id: 10 */
    int32_t *l_45 = &g_46;
    int32_t *l_47 = (void*)0;
    int32_t *l_48 = &g_46;
    int32_t *l_49 = &g_46;
    int32_t *l_50[1];
    int i;
    for (i = 0; i < 1; i++)
        l_50[i] = &g_46;
    --g_52;
    g_51[0][3][1] &= (*l_48);
    for (g_52 = 0; g_52 < 2; g_52 += 1)
    {
        for (g_36 = 0; g_36 < 8; g_36 += 1)
        {
            for (p_24 = 0; p_24 < 3; p_24 += 1)
            {
                g_51[g_52][g_36][p_24] = 0x6F67A21EL;
            }
        }
    }
    for (p_24 = 0; p_24 < 7; p_24 += 1)
    {
        g_40[p_24] = 248UL;
    }
    return l_50[0];
}