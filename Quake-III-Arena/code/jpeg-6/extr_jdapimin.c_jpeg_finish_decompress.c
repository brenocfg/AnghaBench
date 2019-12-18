#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  int /*<<< orphan*/  boolean ;
struct TYPE_14__ {scalar_t__ global_state; scalar_t__ output_scanline; scalar_t__ output_height; TYPE_3__* src; TYPE_2__* inputctl; TYPE_1__* master; int /*<<< orphan*/  buffered_image; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* term_source ) (TYPE_4__*) ;} ;
struct TYPE_12__ {scalar_t__ (* consume_input ) (TYPE_4__*) ;int /*<<< orphan*/  eoi_reached; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* finish_output_pass ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ DSTATE_BUFIMAGE ; 
 scalar_t__ DSTATE_RAW_OK ; 
 scalar_t__ DSTATE_SCANNING ; 
 scalar_t__ DSTATE_STOPPING ; 
 int /*<<< orphan*/  ERREXIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JERR_TOO_LITTLE_DATA ; 
 scalar_t__ JPEG_SUSPENDED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  jpeg_abort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 scalar_t__ stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

boolean
jpeg_finish_decompress (j_decompress_ptr cinfo)
{
  if ((cinfo->global_state == DSTATE_SCANNING ||
       cinfo->global_state == DSTATE_RAW_OK) && ! cinfo->buffered_image) {
    /* Terminate final pass of non-buffered mode */
    if (cinfo->output_scanline < cinfo->output_height)
      ERREXIT(cinfo, JERR_TOO_LITTLE_DATA);
    (*cinfo->master->finish_output_pass) (cinfo);
    cinfo->global_state = DSTATE_STOPPING;
  } else if (cinfo->global_state == DSTATE_BUFIMAGE) {
    /* Finishing after a buffered-image operation */
    cinfo->global_state = DSTATE_STOPPING;
  } else if (cinfo->global_state != DSTATE_STOPPING) {
    /* STOPPING = repeat call after a suspension, anything else is error */
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  }
  /* Read until EOI */
  while (! cinfo->inputctl->eoi_reached) {
    if ((*cinfo->inputctl->consume_input) (cinfo) == JPEG_SUSPENDED)
      return FALSE;		/* Suspend, come back later */
  }
  /* Do final cleanup */
  (*cinfo->src->term_source) (cinfo);
  /* We can use jpeg_abort to release memory and reset global_state */
  jpeg_abort((j_common_ptr) cinfo);
  return TRUE;
}