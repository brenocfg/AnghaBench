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
typedef  int /*<<< orphan*/  htab_trav ;

/* Variables and functions */
 int /*<<< orphan*/  htab_traverse (scalar_t__,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ md_constants ; 

void
traverse_md_constants (htab_trav callback, void *info)
{
  if (md_constants)
    htab_traverse (md_constants, callback, info);
}