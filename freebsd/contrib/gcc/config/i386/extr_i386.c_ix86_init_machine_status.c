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
struct machine_function {int use_fast_prologue_epilogue_nregs; scalar_t__ tls_descriptor_call_expanded_p; } ;

/* Variables and functions */
 struct machine_function* ggc_alloc_cleared (int) ; 

__attribute__((used)) static struct machine_function *
ix86_init_machine_status (void)
{
  struct machine_function *f;

  f = ggc_alloc_cleared (sizeof (struct machine_function));
  f->use_fast_prologue_epilogue_nregs = -1;
  f->tls_descriptor_call_expanded_p = 0;

  return f;
}