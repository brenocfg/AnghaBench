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
typedef  struct Exception* var ;
struct Exception {size_t depth; } ;

/* Variables and functions */

__attribute__((used)) static size_t Exception_Len(var self) {
  struct Exception* e = self;
  return e->depth;
}