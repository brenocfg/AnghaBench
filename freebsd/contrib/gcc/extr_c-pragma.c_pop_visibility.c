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
struct TYPE_2__ {int inpragma; } ;

/* Variables and functions */
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_pop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_visibility ; 
 int /*<<< orphan*/  visibility ; 
 TYPE_1__ visibility_options ; 
 int /*<<< orphan*/  visstack ; 

void
pop_visibility (void)
{
  default_visibility = VEC_pop (visibility, visstack);
  visibility_options.inpragma
    = VEC_length (visibility, visstack) != 0;
}