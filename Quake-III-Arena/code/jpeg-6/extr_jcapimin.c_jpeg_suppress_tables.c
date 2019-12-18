#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* j_compress_ptr ;
typedef  void* boolean ;
struct TYPE_7__ {void* sent_table; } ;
struct TYPE_6__ {void* sent_table; } ;
struct TYPE_5__ {TYPE_3__** ac_huff_tbl_ptrs; TYPE_3__** dc_huff_tbl_ptrs; TYPE_2__** quant_tbl_ptrs; } ;
typedef  TYPE_2__ JQUANT_TBL ;
typedef  TYPE_3__ JHUFF_TBL ;

/* Variables and functions */
 int NUM_HUFF_TBLS ; 
 int NUM_QUANT_TBLS ; 

void
jpeg_suppress_tables (j_compress_ptr cinfo, boolean suppress)
{
  int i;
  JQUANT_TBL * qtbl;
  JHUFF_TBL * htbl;

  for (i = 0; i < NUM_QUANT_TBLS; i++) {
    if ((qtbl = cinfo->quant_tbl_ptrs[i]) != NULL)
      qtbl->sent_table = suppress;
  }

  for (i = 0; i < NUM_HUFF_TBLS; i++) {
    if ((htbl = cinfo->dc_huff_tbl_ptrs[i]) != NULL)
      htbl->sent_table = suppress;
    if ((htbl = cinfo->ac_huff_tbl_ptrs[i]) != NULL)
      htbl->sent_table = suppress;
  }
}