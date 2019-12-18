#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_6__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_21__ {scalar_t__ global_state; scalar_t__ next_scanline; scalar_t__ image_height; scalar_t__ total_iMCU_rows; TYPE_5__* dest; TYPE_4__* marker; TYPE_3__* master; TYPE_2__* coef; TYPE_1__* progress; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* term_destination ) (TYPE_6__*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  (* write_file_trailer ) (TYPE_6__*) ;} ;
struct TYPE_18__ {int /*<<< orphan*/  (* finish_pass ) (TYPE_6__*) ;int /*<<< orphan*/  (* prepare_for_pass ) (TYPE_6__*) ;int /*<<< orphan*/  is_last_pass; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* compress_data ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {long pass_counter; long pass_limit; int /*<<< orphan*/  (* progress_monitor ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  JSAMPIMAGE ;
typedef  scalar_t__ JDIMENSION ;

/* Variables and functions */
 scalar_t__ CSTATE_RAW_OK ; 
 scalar_t__ CSTATE_SCANNING ; 
 scalar_t__ CSTATE_WRCOEFS ; 
 int /*<<< orphan*/  ERREXIT (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_6__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JERR_CANT_SUSPEND ; 
 int /*<<< orphan*/  JERR_TOO_LITTLE_DATA ; 
 int /*<<< orphan*/  jpeg_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*) ; 

void
jpeg_finish_compress (j_compress_ptr cinfo)
{
  JDIMENSION iMCU_row;

  if (cinfo->global_state == CSTATE_SCANNING ||
      cinfo->global_state == CSTATE_RAW_OK) {
    /* Terminate first pass */
    if (cinfo->next_scanline < cinfo->image_height)
      ERREXIT(cinfo, JERR_TOO_LITTLE_DATA);
    (*cinfo->master->finish_pass) (cinfo);
  } else if (cinfo->global_state != CSTATE_WRCOEFS)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Perform any remaining passes */
  while (! cinfo->master->is_last_pass) {
    (*cinfo->master->prepare_for_pass) (cinfo);
    for (iMCU_row = 0; iMCU_row < cinfo->total_iMCU_rows; iMCU_row++) {
      if (cinfo->progress != NULL) {
	cinfo->progress->pass_counter = (long) iMCU_row;
	cinfo->progress->pass_limit = (long) cinfo->total_iMCU_rows;
	(*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
      }
      /* We bypass the main controller and invoke coef controller directly;
       * all work is being done from the coefficient buffer.
       */
      if (! (*cinfo->coef->compress_data) (cinfo, (JSAMPIMAGE) NULL))
	ERREXIT(cinfo, JERR_CANT_SUSPEND);
    }
    (*cinfo->master->finish_pass) (cinfo);
  }
  /* Write EOI, do final cleanup */
  (*cinfo->marker->write_file_trailer) (cinfo);
  (*cinfo->dest->term_destination) (cinfo);
  /* We can use jpeg_abort to release memory and reset global_state */
  jpeg_abort((j_common_ptr) cinfo);
}