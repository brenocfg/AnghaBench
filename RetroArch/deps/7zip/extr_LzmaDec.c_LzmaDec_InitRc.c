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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int code; int range; scalar_t__ needFlush; } ;
typedef  TYPE_1__ CLzmaDec ;

/* Variables and functions */

__attribute__((used)) static void LzmaDec_InitRc(CLzmaDec *p, const uint8_t *data)
{
   p->code = ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 8) | ((uint32_t)data[4]);
   p->range = 0xFFFFFFFF;
   p->needFlush = 0;
}