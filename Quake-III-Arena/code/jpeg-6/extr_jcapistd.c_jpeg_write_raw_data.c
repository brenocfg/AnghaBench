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
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_14__ {scalar_t__ global_state; scalar_t__ next_scanline; scalar_t__ image_height; int max_v_samp_factor; TYPE_3__* coef; TYPE_2__* master; TYPE_1__* progress; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* compress_data ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* pass_startup ) (TYPE_4__*) ;scalar_t__ call_pass_startup; } ;
struct TYPE_11__ {long pass_counter; long pass_limit; int /*<<< orphan*/  (* progress_monitor ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  JSAMPIMAGE ;
typedef  int JDIMENSION ;

/* Variables and functions */
 scalar_t__ CSTATE_RAW_OK ; 
 int DCTSIZE ; 
 int /*<<< orphan*/  ERREXIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JERR_BUFFER_SIZE ; 
 int /*<<< orphan*/  JWRN_TOO_MUCH_DATA ; 
 int /*<<< orphan*/  WARNMS (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ) ; 

JDIMENSION
jpeg_write_raw_data (j_compress_ptr cinfo, JSAMPIMAGE data,
		     JDIMENSION num_lines)
{
  JDIMENSION lines_per_iMCU_row;

  if (cinfo->global_state != CSTATE_RAW_OK)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  if (cinfo->next_scanline >= cinfo->image_height) {
    WARNMS(cinfo, JWRN_TOO_MUCH_DATA);
    return 0;
  }

  /* Call progress monitor hook if present */
  if (cinfo->progress != NULL) {
    cinfo->progress->pass_counter = (long) cinfo->next_scanline;
    cinfo->progress->pass_limit = (long) cinfo->image_height;
    (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
  }

  /* Give master control module another chance if this is first call to
   * jpeg_write_raw_data.  This lets output of the frame/scan headers be
   * delayed so that application can write COM, etc, markers between
   * jpeg_start_compress and jpeg_write_raw_data.
   */
  if (cinfo->master->call_pass_startup)
    (*cinfo->master->pass_startup) (cinfo);

  /* Verify that at least one iMCU row has been passed. */
  lines_per_iMCU_row = cinfo->max_v_samp_factor * DCTSIZE;
  if (num_lines < lines_per_iMCU_row)
    ERREXIT(cinfo, JERR_BUFFER_SIZE);

  /* Directly compress the row. */
  if (! (*cinfo->coef->compress_data) (cinfo, data)) {
    /* If compressor did not consume the whole row, suspend processing. */
    return 0;
  }

  /* OK, we processed one iMCU row. */
  cinfo->next_scanline += lines_per_iMCU_row;
  return lines_per_iMCU_row;
}