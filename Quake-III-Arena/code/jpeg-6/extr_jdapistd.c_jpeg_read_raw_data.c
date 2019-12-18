#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* j_decompress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_11__ {scalar_t__ global_state; scalar_t__ output_scanline; scalar_t__ output_height; int max_v_samp_factor; int min_DCT_scaled_size; TYPE_2__* coef; TYPE_1__* progress; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* decompress_data ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {long pass_counter; long pass_limit; int /*<<< orphan*/  (* progress_monitor ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  JSAMPIMAGE ;
typedef  int JDIMENSION ;

/* Variables and functions */
 scalar_t__ DSTATE_RAW_OK ; 
 int /*<<< orphan*/  ERREXIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 int /*<<< orphan*/  JERR_BUFFER_SIZE ; 
 int /*<<< orphan*/  JWRN_TOO_MUCH_DATA ; 
 int /*<<< orphan*/  WARNMS (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 

JDIMENSION
jpeg_read_raw_data (j_decompress_ptr cinfo, JSAMPIMAGE data,
		    JDIMENSION max_lines)
{
  JDIMENSION lines_per_iMCU_row;

  if (cinfo->global_state != DSTATE_RAW_OK)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  if (cinfo->output_scanline >= cinfo->output_height) {
    WARNMS(cinfo, JWRN_TOO_MUCH_DATA);
    return 0;
  }

  /* Call progress monitor hook if present */
  if (cinfo->progress != NULL) {
    cinfo->progress->pass_counter = (long) cinfo->output_scanline;
    cinfo->progress->pass_limit = (long) cinfo->output_height;
    (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
  }

  /* Verify that at least one iMCU row can be returned. */
  lines_per_iMCU_row = cinfo->max_v_samp_factor * cinfo->min_DCT_scaled_size;
  if (max_lines < lines_per_iMCU_row)
    ERREXIT(cinfo, JERR_BUFFER_SIZE);

  /* Decompress directly into user's buffer. */
  if (! (*cinfo->coef->decompress_data) (cinfo, data))
    return 0;			/* suspension forced, can do nothing more */

  /* OK, we processed one iMCU row. */
  cinfo->output_scanline += lines_per_iMCU_row;
  return lines_per_iMCU_row;
}