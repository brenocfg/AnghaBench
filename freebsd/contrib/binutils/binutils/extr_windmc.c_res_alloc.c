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
typedef  scalar_t__ rc_uint_type ;

/* Variables and functions */
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  res_obstack ; 

void *
res_alloc (rc_uint_type bytes)
{
  return (void *) obstack_alloc (&res_obstack, (size_t) bytes);
}