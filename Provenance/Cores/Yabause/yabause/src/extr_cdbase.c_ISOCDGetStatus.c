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
struct TYPE_2__ {scalar_t__ session_num; } ;

/* Variables and functions */
 TYPE_1__ disc ; 

__attribute__((used)) static int ISOCDGetStatus(void) {
   return disc.session_num > 0 ? 0 : 2;
}