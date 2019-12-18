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
typedef  scalar_t__ var ;
typedef  int /*<<< orphan*/  uint64_t ;
struct Table {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t Table_Swapspace_Hash(struct Table* t, var space) {
  return *((uint64_t*)space);
}