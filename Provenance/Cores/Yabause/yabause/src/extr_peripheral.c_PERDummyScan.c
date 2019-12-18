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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

u32 PERDummyScan(u32 flags) {
   // Scan and return next action based on flags value
   // See PERSF_* in peripheral.h for full list of flags.
   // If no specified flags are supported return 0

   return 0;
}