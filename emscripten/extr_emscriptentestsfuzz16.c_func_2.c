#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct S5 {int dummy; } ;
struct S4 {int dummy; } ;
struct S3 {int dummy; } ;
struct S1 {int f1; } ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_2__ {int f1; int f0; } ;

/* Variables and functions */
 TYPE_1__ g_22 ; 
 int /*<<< orphan*/ * g_252 ; 
 struct S1* g_42 ; 
 scalar_t__* g_494 ; 
 int g_84 ; 
 int g_94 ; 
 int safe_add_func_uint32_t_u_u (int,int) ; 
 int safe_sub_func_int8_t_s_s (int,int) ; 

__attribute__((used)) static struct S1  func_2(struct S1  p_3, struct S4  p_4, struct S3  p_5, const struct S3  p_6, struct S5  p_7)
{ /* block id: 578 */
    const int8_t **l_1080 = &g_252;
    for (g_84 = 8; (g_84 != (-5)); g_84 = safe_sub_func_int8_t_s_s(g_84, 7))
    { /* block id: 581 */
        for (g_22.f1 = 0; (g_22.f1 <= 22); g_22.f1 = safe_add_func_uint32_t_u_u(g_22.f1, 1))
        { /* block id: 584 */
            for (g_94 = 0; (g_94 <= 2); g_94 += 1)
            { /* block id: 587 */
                for (g_22.f0 = 2; (g_22.f0 <= 8); g_22.f0 += 1)
                { /* block id: 590 */
                    int i;
                    if (g_494[(g_94 + 1)])
                        break;
                }
                for (p_3.f1 = 0; (p_3.f1 <= 2); p_3.f1 += 1)
                { /* block id: 595 */
                    int i;
                    if (g_494[p_3.f1])
                        break;
                }
                return (*g_42);
            }
            return p_3;
        }
    }
    l_1080 = l_1080;
    return (*g_42);
}