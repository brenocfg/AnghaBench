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
typedef  int u32 ;
struct TYPE_3__ {int* data_array; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */

__attribute__((used)) static u32 sh2_read8_da(u32 a, SH2 *sh2)
{
  return sh2->data_array[(a & 0xfff) ^ 1];
}