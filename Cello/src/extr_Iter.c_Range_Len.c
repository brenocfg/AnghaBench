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
typedef  struct Range* var ;
struct Range {int step; int stop; int start; } ;

/* Variables and functions */

__attribute__((used)) static size_t Range_Len(var self) {
  struct Range* r = self;
  if (r->step == 0) { return 0; }
  if (r->step  > 0) { return ((r->stop-1) - r->start) /  r->step + 1; }
  if (r->step  < 0) { return ((r->stop-1) - r->start) / -r->step + 1; }
  return 0;
}