#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  scalar_t__ boolean ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  sent_table; scalar_t__* quantval; } ;
struct TYPE_6__ {scalar_t__ global_state; TYPE_2__** quant_tbl_ptrs; } ;
typedef  TYPE_2__ JQUANT_TBL ;

/* Variables and functions */
 scalar_t__ CSTATE_START ; 
 int DCTSIZE2 ; 
 int /*<<< orphan*/  ERREXIT1 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JERR_BAD_STATE ; 
 TYPE_2__* jpeg_alloc_quant_table (int /*<<< orphan*/ ) ; 

void
jpeg_add_quant_table (j_compress_ptr cinfo, int which_tbl,
		      const unsigned int *basic_table,
		      int scale_factor, boolean force_baseline)
/* Define a quantization table equal to the basic_table times
 * a scale factor (given as a percentage).
 * If force_baseline is TRUE, the computed quantization table entries
 * are limited to 1..255 for JPEG baseline compatibility.
 */
{
  JQUANT_TBL ** qtblptr = & cinfo->quant_tbl_ptrs[which_tbl];
  int i;
  long temp;

  /* Safety check to ensure start_compress not called yet. */
  if (cinfo->global_state != CSTATE_START)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);

  if (*qtblptr == NULL)
    *qtblptr = jpeg_alloc_quant_table((j_common_ptr) cinfo);

  for (i = 0; i < DCTSIZE2; i++) {
    temp = ((long) basic_table[i] * scale_factor + 50L) / 100L;
    /* limit the values to the valid range */
    if (temp <= 0L) temp = 1L;
    if (temp > 32767L) temp = 32767L; /* max quantizer needed for 12 bits */
    if (force_baseline && temp > 255L)
      temp = 255L;		/* limit to baseline range if requested */
    (*qtblptr)->quantval[i] = (UINT16) temp;
  }

  /* Initialize sent_table FALSE so table will be written to JPEG file. */
  (*qtblptr)->sent_table = FALSE;
}