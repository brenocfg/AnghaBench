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
typedef  int uint64_t ;
struct TYPE_2__ {int numer; int denom; } ;

/* Variables and functions */
 TYPE_1__ timebase_info ; 

__attribute__((used)) static uint64_t abs_to_nanos(uint64_t abs)   { return abs * timebase_info.numer / timebase_info.denom; }