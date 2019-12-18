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

/* Variables and functions */
 scalar_t__ flag_expensive_optimizations ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  optimize_size ; 

__attribute__((used)) static bool
gate_duplicate_computed_gotos (void)
{
  return (optimize > 0 && flag_expensive_optimizations && !optimize_size);
}