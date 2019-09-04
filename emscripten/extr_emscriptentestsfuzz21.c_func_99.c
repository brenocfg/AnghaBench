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
typedef  union U0 {int dummy; } U0 ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/ * g_4 ; 
 int /*<<< orphan*/  g_91 ; 

__attribute__((used)) static const int32_t * func_99(uint16_t  p_100, int16_t  p_101, union U0  p_102, int64_t * const  p_103, int64_t * p_104)
{ /* block id: 32 */
    int64_t * const l_111 = &g_91;
    int64_t * const *l_110 = &l_111;
    int64_t * const **l_109 = &l_110;
    const int32_t *l_112[3][1][6];
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            for (k = 0; k < 6; k++)
                l_112[i][j][k] = &g_4[3];
        }
    }
    (*l_109) = &p_103;
    return l_112[2][0][0];
}