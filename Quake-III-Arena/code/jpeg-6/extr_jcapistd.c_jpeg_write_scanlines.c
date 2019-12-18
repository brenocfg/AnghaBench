#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_13__ {scalar_t__ global_state; scalar_t__ next_scanline; scalar_t__ image_height; TYPE_3__* main; TYPE_2__* master; TYPE_1__* progress; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* process_data ) (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* pass_startup ) (TYPE_4__*) ;scalar_t__ call_pass_startup; } ;
struct TYPE_10__ {long pass_counter; long pass_limit; int /*<<< orphan*/  (* progress_monitor ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  JSAMPARRAY ;
typedef  scalar_t__ JDIMENSION ;

/* Variables and functions */
 scalar_t__ CSTATE_SCANNING ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JWRN_TOO_MUCH_DATA ; 
 int /*<<< orphan*/  WARNMS (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 

JDIMENSION
jpeg_write_scanlines (j_compress_ptr cinfo, JSAMPARRAY scanlines,
		      JDIMENSION num_lines)
{
  JDIMENSION row_ctr, rows_left;

  if (cinfo->global_state != CSTATE_SCANNING)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  if (cinfo->next_scanline >= cinfo->image_height)
    WARNMS(cinfo, JWRN_TOO_MUCH_DATA);

  /* Call progress monitor hook if present */
  if (cinfo->progress != NULL) {
    cinfo->progress->pass_counter = (long) cinfo->next_scanline;
    cinfo->progress->pass_limit = (long) cinfo->image_height;
    (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
  }

  /* Give master control module another chance if this is first call to
   * jpeg_write_scanlines.  This lets output of the frame/scan headers be
   * delayed so that application can write COM, etc, markers between
   * jpeg_start_compress and jpeg_write_scanlines.
   */
  if (cinfo->master->call_pass_startup)
    (*cinfo->master->pass_startup) (cinfo);

  /* Ignore any extra scanlines at bottom of image. */
  rows_left = cinfo->image_height - cinfo->next_scanline;
  if (num_lines > rows_left)
    num_lines = rows_left;

  row_ctr = 0;
  (*cinfo->main->process_data) (cinfo, scanlines, &row_ctr, num_lines);
  cinfo->next_scanline += row_ctr;
  return row_ctr;
}