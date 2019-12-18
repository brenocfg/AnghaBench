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
typedef  size_t hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
struct_ptr_hash (const void *a)
{
  const void * const * x = (const void * const *) a;
  return (size_t)*x >> 4;
}