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
 int /*<<< orphan*/  frag_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  frag_wane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
new_frag (void)
{
  frag_wane (frag_now);
  frag_new (0);
}