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
 void* antloc ; 
 void* comp ; 
 void* hoist_exprs ; 
 void* hoist_vbein ; 
 void* hoist_vbeout ; 
 void* sbitmap_vector_alloc (int,int) ; 
 void* transp ; 
 void* transpout ; 

__attribute__((used)) static void
alloc_code_hoist_mem (int n_blocks, int n_exprs)
{
  antloc = sbitmap_vector_alloc (n_blocks, n_exprs);
  transp = sbitmap_vector_alloc (n_blocks, n_exprs);
  comp = sbitmap_vector_alloc (n_blocks, n_exprs);

  hoist_vbein = sbitmap_vector_alloc (n_blocks, n_exprs);
  hoist_vbeout = sbitmap_vector_alloc (n_blocks, n_exprs);
  hoist_exprs = sbitmap_vector_alloc (n_blocks, n_exprs);
  transpout = sbitmap_vector_alloc (n_blocks, n_exprs);
}