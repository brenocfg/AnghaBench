#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_12__ {scalar_t__ global_state; int /*<<< orphan*/  input_scan_number; int /*<<< orphan*/  output_scan_number; scalar_t__ total_iMCU_rows; TYPE_2__* progress; TYPE_1__* inputctl; scalar_t__ buffered_image; } ;
struct TYPE_11__ {scalar_t__ pass_counter; scalar_t__ pass_limit; int /*<<< orphan*/  (* progress_monitor ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int (* consume_input ) (TYPE_3__*) ;scalar_t__ has_multiple_scans; } ;

/* Variables and functions */
 scalar_t__ DSTATE_BUFIMAGE ; 
 scalar_t__ DSTATE_PRELOAD ; 
 scalar_t__ DSTATE_PRESCAN ; 
 scalar_t__ DSTATE_READY ; 
 int /*<<< orphan*/  ERREXIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JERR_NOT_COMPILED ; 
 int JPEG_REACHED_EOI ; 
 int JPEG_REACHED_SOS ; 
 int JPEG_ROW_COMPLETED ; 
 int JPEG_SUSPENDED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  jinit_master_decompress (TYPE_3__*) ; 
 int /*<<< orphan*/  output_pass_setup (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_3__*) ; 

boolean
jpeg_start_decompress (j_decompress_ptr cinfo)
{
  if (cinfo->global_state == DSTATE_READY) {
    /* First call: initialize master control, select active modules */
    jinit_master_decompress(cinfo);
    if (cinfo->buffered_image) {
      /* No more work here; expecting jpeg_start_output next */
      cinfo->global_state = DSTATE_BUFIMAGE;
      return TRUE;
    }
    cinfo->global_state = DSTATE_PRELOAD;
  }
  if (cinfo->global_state == DSTATE_PRELOAD) {
    /* If file has multiple scans, absorb them all into the coef buffer */
    if (cinfo->inputctl->has_multiple_scans) {
#ifdef D_MULTISCAN_FILES_SUPPORTED
      for (;;) {
	int retcode;
	/* Call progress monitor hook if present */
	if (cinfo->progress != NULL)
	  (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
	/* Absorb some more input */
	retcode = (*cinfo->inputctl->consume_input) (cinfo);
	if (retcode == JPEG_SUSPENDED)
	  return FALSE;
	if (retcode == JPEG_REACHED_EOI)
	  break;
	/* Advance progress counter if appropriate */
	if (cinfo->progress != NULL &&
	    (retcode == JPEG_ROW_COMPLETED || retcode == JPEG_REACHED_SOS)) {
	  if (++cinfo->progress->pass_counter >= cinfo->progress->pass_limit) {
	    /* jdmaster underestimated number of scans; ratchet up one scan */
	    cinfo->progress->pass_limit += (long) cinfo->total_iMCU_rows;
	  }
	}
      }
#else
      ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif /* D_MULTISCAN_FILES_SUPPORTED */
    }
    cinfo->output_scan_number = cinfo->input_scan_number;
  } else if (cinfo->global_state != DSTATE_PRESCAN)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Perform any dummy output passes, and set up for the final pass */
  return output_pass_setup(cinfo);
}