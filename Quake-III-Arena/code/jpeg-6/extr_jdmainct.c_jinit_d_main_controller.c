#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct jpeg_d_main_controller {int dummy; } ;
typedef  TYPE_4__* my_main_ptr ;
struct TYPE_14__ {int v_samp_factor; int DCT_scaled_size; int width_in_blocks; } ;
typedef  TYPE_5__ jpeg_component_info ;
typedef  TYPE_6__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_15__ {int min_DCT_scaled_size; int num_components; TYPE_3__* mem; TYPE_5__* comp_info; TYPE_2__* upsample; struct jpeg_d_main_controller* main; } ;
struct TYPE_10__ {int /*<<< orphan*/  start_pass; } ;
struct TYPE_13__ {int /*<<< orphan*/ * buffer; TYPE_1__ pub; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* alloc_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {scalar_t__ need_context_rows; } ;
typedef  int /*<<< orphan*/  JDIMENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERR_BAD_BUFFER_MODE ; 
 int /*<<< orphan*/  JERR_NOTIMPL ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_funny_pointers (TYPE_6__*) ; 
 int /*<<< orphan*/  my_main_controller ; 
 int /*<<< orphan*/  start_pass_main ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
jinit_d_main_controller (j_decompress_ptr cinfo, boolean need_full_buffer)
{
  // bk001204 - no use main
  my_main_ptr jmain;
  int ci, rgroup, ngroups;
  jpeg_component_info *compptr;

  jmain = (my_main_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_main_controller));
  cinfo->main = (struct jpeg_d_main_controller *) jmain;
  jmain->pub.start_pass = start_pass_main;

  if (need_full_buffer)		/* shouldn't happen */
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);

  /* Allocate the workspace.
   * ngroups is the number of row groups we need.
   */
  if (cinfo->upsample->need_context_rows) {
    if (cinfo->min_DCT_scaled_size < 2) /* unsupported, see comments above */
      ERREXIT(cinfo, JERR_NOTIMPL);
    alloc_funny_pointers(cinfo); /* Alloc space for xbuffer[] lists */
    ngroups = cinfo->min_DCT_scaled_size + 2;
  } else {
    ngroups = cinfo->min_DCT_scaled_size;
  }

  for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
       ci++, compptr++) {
    rgroup = (compptr->v_samp_factor * compptr->DCT_scaled_size) /
      cinfo->min_DCT_scaled_size; /* height of a row group of component */
    jmain->buffer[ci] = (*cinfo->mem->alloc_sarray)
			((j_common_ptr) cinfo, JPOOL_IMAGE,
			 compptr->width_in_blocks * compptr->DCT_scaled_size,
			 (JDIMENSION) (rgroup * ngroups));
  }
}