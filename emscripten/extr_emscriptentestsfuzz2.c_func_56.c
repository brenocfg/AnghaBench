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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  const int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_2__ {int f4; } ;

/* Variables and functions */
 TYPE_1__ g_18 ; 
 int /*<<< orphan*/ * g_36 ; 

__attribute__((used)) static const int8_t * func_56(int32_t * p_57, int16_t  p_58, uint16_t * p_59, int8_t * p_60)
{ /* block id: 16 */
    for (g_18.f4 = 27; (g_18.f4 >= 55); g_18.f4++)
    { /* block id: 19 */
        (*p_57) ^= g_36[3];
    }
    return p_60;
}