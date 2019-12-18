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
 int /*<<< orphan*/  align_frag ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  s_align_bytes (int) ; 

__attribute__((used)) static void
dot_align (int arg)
{
  /* The current frag is an alignment frag.  */
  align_frag = frag_now;
  s_align_bytes (arg);
}