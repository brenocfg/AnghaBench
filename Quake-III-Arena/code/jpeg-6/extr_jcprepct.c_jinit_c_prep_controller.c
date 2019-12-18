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
struct jpeg_c_prep_controller {int dummy; } ;
typedef  TYPE_4__* my_prep_ptr ;
struct TYPE_14__ {long h_samp_factor; scalar_t__ width_in_blocks; } ;
typedef  TYPE_5__ jpeg_component_info ;
typedef  TYPE_6__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_15__ {int num_components; long max_h_samp_factor; scalar_t__ max_v_samp_factor; TYPE_3__* mem; TYPE_5__* comp_info; TYPE_1__* downsample; struct jpeg_c_prep_controller* prep; } ;
struct TYPE_11__ {int /*<<< orphan*/  pre_process_data; int /*<<< orphan*/  start_pass; } ;
struct TYPE_13__ {int /*<<< orphan*/ * color_buf; TYPE_2__ pub; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* alloc_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {scalar_t__ need_context_rows; } ;
typedef  int /*<<< orphan*/  JDIMENSION ;

/* Variables and functions */
 long DCTSIZE ; 
 int /*<<< orphan*/  ERREXIT (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERR_BAD_BUFFER_MODE ; 
 int /*<<< orphan*/  JERR_NOT_COMPILED ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_context_buffer (TYPE_6__*) ; 
 int /*<<< orphan*/  my_prep_controller ; 
 int /*<<< orphan*/  pre_process_context ; 
 int /*<<< orphan*/  pre_process_data ; 
 int /*<<< orphan*/  start_pass_prep ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jinit_c_prep_controller (j_compress_ptr cinfo, boolean need_full_buffer)
{
  my_prep_ptr prep;
  int ci;
  jpeg_component_info * compptr;

  if (need_full_buffer)		/* safety check */
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);

  prep = (my_prep_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_prep_controller));
  cinfo->prep = (struct jpeg_c_prep_controller *) prep;
  prep->pub.start_pass = start_pass_prep;

  /* Allocate the color conversion buffer.
   * We make the buffer wide enough to allow the downsampler to edge-expand
   * horizontally within the buffer, if it so chooses.
   */
  if (cinfo->downsample->need_context_rows) {
    /* Set up to provide context rows */
#ifdef CONTEXT_ROWS_SUPPORTED
    prep->pub.pre_process_data = pre_process_context;
    create_context_buffer(cinfo);
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
  } else {
    /* No context, just make it tall enough for one row group */
    prep->pub.pre_process_data = pre_process_data;
    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      prep->color_buf[ci] = (*cinfo->mem->alloc_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE,
	 (JDIMENSION) (((long) compptr->width_in_blocks * DCTSIZE *
			cinfo->max_h_samp_factor) / compptr->h_samp_factor),
	 (JDIMENSION) cinfo->max_v_samp_factor);
    }
  }
}