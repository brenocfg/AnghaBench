#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jvirt_barray_ptr ;
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_12__ {scalar_t__ global_state; TYPE_3__* coef; scalar_t__ total_iMCU_rows; TYPE_2__* progress; TYPE_1__* inputctl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * coef_arrays; } ;
struct TYPE_10__ {scalar_t__ pass_counter; scalar_t__ pass_limit; int /*<<< orphan*/  (* progress_monitor ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int (* consume_input ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ DSTATE_RDCOEFS ; 
 scalar_t__ DSTATE_READY ; 
 scalar_t__ DSTATE_STOPPING ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int JPEG_REACHED_EOI ; 
 int JPEG_REACHED_SOS ; 
 int JPEG_ROW_COMPLETED ; 
 int JPEG_SUSPENDED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  transdecode_master_selection (TYPE_4__*) ; 

jvirt_barray_ptr *
jpeg_read_coefficients (j_decompress_ptr cinfo)
{
  if (cinfo->global_state == DSTATE_READY) {
    /* First call: initialize active modules */
    transdecode_master_selection(cinfo);
    cinfo->global_state = DSTATE_RDCOEFS;
  } else if (cinfo->global_state != DSTATE_RDCOEFS)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Absorb whole file into the coef buffer */
  for (;;) {
    int retcode;
    /* Call progress monitor hook if present */
    if (cinfo->progress != NULL)
      (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
    /* Absorb some more input */
    retcode = (*cinfo->inputctl->consume_input) (cinfo);
    if (retcode == JPEG_SUSPENDED)
      return NULL;
    if (retcode == JPEG_REACHED_EOI)
      break;
    /* Advance progress counter if appropriate */
    if (cinfo->progress != NULL &&
	(retcode == JPEG_ROW_COMPLETED || retcode == JPEG_REACHED_SOS)) {
      if (++cinfo->progress->pass_counter >= cinfo->progress->pass_limit) {
	/* startup underestimated number of scans; ratchet up one scan */
	cinfo->progress->pass_limit += (long) cinfo->total_iMCU_rows;
      }
    }
  }
  /* Set state so that jpeg_finish_decompress does the right thing */
  cinfo->global_state = DSTATE_STOPPING;
  return cinfo->coef->coef_arrays;
}