#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jpeg_inverse_dct {int dummy; } ;
typedef  TYPE_3__* my_idct_ptr ;
struct TYPE_10__ {scalar_t__ dct_table; } ;
typedef  TYPE_4__ jpeg_component_info ;
typedef  TYPE_5__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_11__ {int num_components; TYPE_2__* mem; TYPE_4__* comp_info; struct jpeg_inverse_dct* idct; } ;
struct TYPE_7__ {int /*<<< orphan*/  start_pass; } ;
struct TYPE_9__ {int* cur_method; TYPE_1__ pub; } ;
struct TYPE_8__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  MEMZERO (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiplier_table ; 
 int /*<<< orphan*/  my_idct_controller ; 
 int /*<<< orphan*/  start_pass ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jinit_inverse_dct (j_decompress_ptr cinfo)
{
  my_idct_ptr idct;
  int ci;
  jpeg_component_info *compptr;

  idct = (my_idct_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_idct_controller));
  cinfo->idct = (struct jpeg_inverse_dct *) idct;
  idct->pub.start_pass = start_pass;

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    /* Allocate and pre-zero a multiplier table for each component */
    compptr->dct_table =
      (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  SIZEOF(multiplier_table));
    MEMZERO(compptr->dct_table, SIZEOF(multiplier_table));
    /* Mark multiplier table not yet set up for any method */
    idct->cur_method[ci] = -1;
  }
}