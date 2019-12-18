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
struct jpeg_c_main_controller {int dummy; } ;
typedef  TYPE_3__* my_main_ptr ;
struct TYPE_11__ {int width_in_blocks; int v_samp_factor; scalar_t__ height_in_blocks; } ;
typedef  TYPE_4__ jpeg_component_info ;
typedef  TYPE_5__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
struct TYPE_12__ {int num_components; TYPE_2__* mem; TYPE_4__* comp_info; scalar_t__ raw_data_in; struct jpeg_c_main_controller* main; } ;
struct TYPE_8__ {int /*<<< orphan*/  start_pass; } ;
struct TYPE_10__ {int /*<<< orphan*/ * buffer; int /*<<< orphan*/ ** whole_image; TYPE_1__ pub; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* alloc_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/ * (* request_virt_sarray ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ;scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int JDIMENSION ;

/* Variables and functions */
 int DCTSIZE ; 
 int /*<<< orphan*/  ERREXIT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_BUFFER_MODE ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 scalar_t__ jround_up (long,long) ; 
 int /*<<< orphan*/  my_main_controller ; 
 int /*<<< orphan*/  start_pass_main ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
jinit_c_main_controller (j_compress_ptr cinfo, boolean need_full_buffer)
{
  // bk001204 - don't use main
  my_main_ptr jmain;
  int ci;
  jpeg_component_info *compptr;

  jmain = (my_main_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_main_controller));
  cinfo->main = (struct jpeg_c_main_controller *) jmain;
  jmain->pub.start_pass = start_pass_main;

  /* We don't need to create a buffer in raw-data mode. */
  if (cinfo->raw_data_in)
    return;

  /* Create the buffer.  It holds downsampled data, so each component
   * may be of a different size.
   */
  if (need_full_buffer) {
#ifdef FULL_MAIN_BUFFER_SUPPORTED
    /* Allocate a full-image virtual array for each component */
    /* Note we pad the bottom to a multiple of the iMCU height */
    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      jmain->whole_image[ci] = (*cinfo->mem->request_virt_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE, FALSE,
	 compptr->width_in_blocks * DCTSIZE,
	 (JDIMENSION) jround_up((long) compptr->height_in_blocks,
				(long) compptr->v_samp_factor) * DCTSIZE,
	 (JDIMENSION) (compptr->v_samp_factor * DCTSIZE));
    }
#else
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
#endif
  } else {
#ifdef FULL_MAIN_BUFFER_SUPPORTED
    jmain->whole_image[0] = NULL; /* flag for no virtual arrays */
#endif
    /* Allocate a strip buffer for each component */
    for (ci = 0, compptr = cinfo->comp_info; ci < cinfo->num_components;
	 ci++, compptr++) {
      jmain->buffer[ci] = (*cinfo->mem->alloc_sarray)
	((j_common_ptr) cinfo, JPOOL_IMAGE,
	 compptr->width_in_blocks * DCTSIZE,
	 (JDIMENSION) (compptr->v_samp_factor * DCTSIZE));
    }
  }
}