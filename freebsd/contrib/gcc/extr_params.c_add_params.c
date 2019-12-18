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
typedef  int /*<<< orphan*/  param_info ;

/* Variables and functions */
 scalar_t__ compiler_params ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 size_t num_compiler_params ; 
 scalar_t__ xrealloc (scalar_t__,size_t) ; 

void
add_params (const param_info params[], size_t n)
{
  /* Allocate enough space for the new parameters.  */
  compiler_params = xrealloc (compiler_params,
			      (num_compiler_params + n) * sizeof (param_info));
  /* Copy them into the table.  */
  memcpy (compiler_params + num_compiler_params,
	  params,
	  n * sizeof (param_info));
  /* Keep track of how many parameters we have.  */
  num_compiler_params += n;
}