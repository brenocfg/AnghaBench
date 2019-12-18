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
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 TYPE_1__ ym2413 ; 

unsigned int YM2413Read(unsigned int a)
{
  /* D0=latched bit, D1-D2 need to be zero (Master System specific) */
  return 0xF8 | ym2413.status;
}