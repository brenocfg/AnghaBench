#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct jpeg_d_coef_controller {int dummy; } ;
typedef  TYPE_3__* my_coef_ptr ;
struct TYPE_11__ {int v_samp_factor; scalar_t__ height_in_blocks; scalar_t__ h_samp_factor; scalar_t__ width_in_blocks; } ;
typedef  TYPE_4__ jpeg_component_info ;
typedef  TYPE_5__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_12__ {int num_components; TYPE_1__* mem; scalar_t__ progressive_mode; TYPE_4__* comp_info; struct jpeg_d_coef_controller* coef; } ;
struct TYPE_9__ {int /*<<< orphan*/ * coef_arrays; int /*<<< orphan*/  decompress_data; int /*<<< orphan*/  consume_data; int /*<<< orphan*/  start_output_pass; int /*<<< orphan*/  start_input_pass; } ;
struct TYPE_10__ {TYPE_2__ pub; scalar_t__* MCU_buffer; int /*<<< orphan*/ * whole_image; int /*<<< orphan*/ * coef_bits_latch; } ;
struct TYPE_8__ {scalar_t__ (* alloc_large ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* request_virt_barray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  JDIMENSION ;
typedef  scalar_t__ JBLOCKROW ;

/* Variables and functions */
 int D_MAX_BLOCKS_IN_MCU ; 
 int /*<<< orphan*/  ERREXIT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JBLOCK ; 
 int /*<<< orphan*/  JERR_NOT_COMPILED ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int SIZEOF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  consume_data ; 
 int /*<<< orphan*/  decompress_data ; 
 int /*<<< orphan*/  decompress_onepass ; 
 int /*<<< orphan*/  dummy_consume_data ; 
 scalar_t__ jround_up (long,long) ; 
 int /*<<< orphan*/  my_coef_controller ; 
 int /*<<< orphan*/  start_input_pass ; 
 int /*<<< orphan*/  start_output_pass ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
jinit_d_coef_controller (j_decompress_ptr cinfo, boolean need_full_buffer)
{
  my_coef_ptr coef;

  coef = (my_coef_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_coef_controller));
  cinfo->coef = (struct jpeg_d_coef_controller *) coef;
  coef->pub.start_input_pass = start_input_pass;
  coef->pub.start_output_pass = start_output_pass;
#ifdef BLOCK_SMOOTHING_SUPPORTED
  coef->coef_bits_latch = NULL;
#endif

  /* Create the coefficient buffer. */
  if (need_full_buffer) {
#ifdef D_MULTISCAN_FILES_SUPPORTED
    /* Allocate a full-image virtual array for each component, */
    /* padded to a multiple of samp_factor DCT blocks in each direction. */
    /* Note we ask for a pre-zeroed array. */
    int ci, access_rows;
    jpeg_component_info *compptr;

    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      access_rows = compptr->v_samp_factor;
#ifdef BLOCK_SMOOTHING_SUPPORTED
      /* If block smoothing could be used, need a bigger window */
      if (cinfo->progressive_mode)
	access_rows *= 3;
#endif
      coef->whole_image[ci] = (*cinfo->mem->request_virt_barray)
	((j_common_ptr) cinfo, JPOOL_IMAGE, TRUE,
	 (JDIMENSION) jround_up((long) compptr->width_in_blocks,
				(long) compptr->h_samp_factor),
	 (JDIMENSION) jround_up((long) compptr->height_in_blocks,
				(long) compptr->v_samp_factor),
	 (JDIMENSION) access_rows);
    }
    coef->pub.consume_data = consume_data;
    coef->pub.decompress_data = decompress_data;
    coef->pub.coef_arrays = coef->whole_image; /* link to virtual arrays */
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif
  } else {
    /* We only need a single-MCU buffer. */
    JBLOCKROW buffer;
    int i;

    buffer = (JBLOCKROW)
      (*cinfo->mem->alloc_large) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  D_MAX_BLOCKS_IN_MCU * SIZEOF(JBLOCK));
    for (i = 0; i < D_MAX_BLOCKS_IN_MCU; i++) {
      coef->MCU_buffer[i] = buffer + i;
    }
    coef->pub.consume_data = dummy_consume_data;
    coef->pub.decompress_data = decompress_onepass;
    coef->pub.coef_arrays = NULL; /* flag for no virtual arrays */
  }
}