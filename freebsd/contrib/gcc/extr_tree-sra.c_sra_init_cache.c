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
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 void* sra_type_decomp_cache ; 
 void* sra_type_inst_cache ; 

void 
sra_init_cache (void)
{
  if (sra_type_decomp_cache) 
    return;

  sra_type_decomp_cache = BITMAP_ALLOC (NULL);
  sra_type_inst_cache = BITMAP_ALLOC (NULL);
}