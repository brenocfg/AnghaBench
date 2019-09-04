#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int e; int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ softfloat ;
typedef  int int32_t ;

/* Variables and functions */
 int mul32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int32_t quantize_value(int32_t value, softfloat quant)
{
    int32_t offset = 1 << (quant.e - 1);

    value = mul32(value, quant.m) + offset;
    value = value >> quant.e;
    return value;
}