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
struct cp_binding_level {scalar_t__ kind; struct cp_binding_level* level_chain; } ;

/* Variables and functions */
 struct cp_binding_level* current_binding_level ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ sk_omp ; 

bool
check_omp_return (void)
{
  struct cp_binding_level *b;
  for (b = current_binding_level; b ; b = b->level_chain)
    if (b->kind == sk_omp)
      {
	error ("invalid exit from OpenMP structured block");
	return false;
      }
  return true;
}