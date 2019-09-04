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
struct TYPE_3__ {scalar_t__ insert_len_; } ;
typedef  TYPE_1__ Command ;

/* Variables and functions */

__attribute__((used)) static size_t CountLiterals(const Command* cmds, const size_t num_commands) {
  /* Count how many we have. */
  size_t total_length = 0;
  size_t i;
  for (i = 0; i < num_commands; ++i) {
    total_length += cmds[i].insert_len_;
  }
  return total_length;
}