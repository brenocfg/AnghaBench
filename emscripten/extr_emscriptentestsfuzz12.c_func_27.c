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
typedef  union U3 {int dummy; } U3 ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
struct TYPE_2__ {int f3; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_10 ; 
 TYPE_1__ g_123 ; 
 union U3 g_62 ; 

__attribute__((used)) static int8_t * func_27(const union U3  p_28, const union U3  p_29, int8_t * p_30, int8_t * p_31, int8_t  p_32)
{ /* block id: 314 */
    union U3 *l_459 = &g_62;
    union U3 *l_461 = &g_62;
    union U3 **l_460 = &l_461;
    int32_t l_462 = 0x5FFEF395L;
    int32_t *l_463 = &g_123.f3;
    int8_t *l_464 = &g_10;
    (*l_460) = (l_459 = l_459);
    (*l_463) &= l_462;
    return l_464;
}