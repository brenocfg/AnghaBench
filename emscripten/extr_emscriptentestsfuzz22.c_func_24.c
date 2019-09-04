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
struct S0 {long f0; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int g_104 ; 

__attribute__((used)) static int32_t  func_24(int64_t  p_25, struct S0  p_26)
{ /* block id: 373 */
    int32_t *l_737[2][1];
    uint32_t l_738 = 0x6A2B6200L;
    int i, j;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 1; j++)
            l_737[i][j] = &g_104;
    }
    p_26.f0 = (-1L);
    return l_738;
}