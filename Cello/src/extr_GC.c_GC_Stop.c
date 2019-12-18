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
typedef  struct GC* var ;
struct GC {int running; } ;

/* Variables and functions */

__attribute__((used)) static void GC_Stop(var self) {
  struct GC* gc = self;
  gc->running = false;
}