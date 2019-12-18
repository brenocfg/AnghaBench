#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct jpeg_forward_dct {int dummy; } ;
typedef  TYPE_3__* my_fdct_ptr ;
typedef  TYPE_4__* j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;
struct TYPE_10__ {int dct_method; struct jpeg_forward_dct* fdct; TYPE_1__* mem; } ;
struct TYPE_8__ {void* forward_DCT; int /*<<< orphan*/  start_pass; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** float_divisors; int /*<<< orphan*/ ** divisors; int /*<<< orphan*/  do_float_dct; TYPE_2__ pub; int /*<<< orphan*/  do_dct; } ;
struct TYPE_7__ {scalar_t__ (* alloc_small ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (TYPE_4__*,int /*<<< orphan*/ ) ; 
#define  JDCT_FLOAT 130 
#define  JDCT_IFAST 129 
#define  JDCT_ISLOW 128 
 int /*<<< orphan*/  JERR_NOT_COMPILED ; 
 int /*<<< orphan*/  JPOOL_IMAGE ; 
 int NUM_QUANT_TBLS ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ ) ; 
 void* forward_DCT ; 
 void* forward_DCT_float ; 
 int /*<<< orphan*/  jpeg_fdct_float ; 
 int /*<<< orphan*/  jpeg_fdct_ifast ; 
 int /*<<< orphan*/  jpeg_fdct_islow ; 
 int /*<<< orphan*/  my_fdct_controller ; 
 int /*<<< orphan*/  start_pass_fdctmgr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
jinit_forward_dct (j_compress_ptr cinfo)
{
  my_fdct_ptr fdct;
  int i;

  fdct = (my_fdct_ptr)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				SIZEOF(my_fdct_controller));
  cinfo->fdct = (struct jpeg_forward_dct *) fdct;
  fdct->pub.start_pass = start_pass_fdctmgr;

  switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
  case JDCT_ISLOW:
    fdct->pub.forward_DCT = forward_DCT;
    fdct->do_dct = jpeg_fdct_islow;
    break;
#endif
#ifdef DCT_IFAST_SUPPORTED
  case JDCT_IFAST:
    fdct->pub.forward_DCT = forward_DCT;
    fdct->do_dct = jpeg_fdct_ifast;
    break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
  case JDCT_FLOAT:
    fdct->pub.forward_DCT = forward_DCT_float;
    fdct->do_float_dct = jpeg_fdct_float;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_NOT_COMPILED);
    break;
  }

  /* Mark divisor tables unallocated */
  for (i = 0; i < NUM_QUANT_TBLS; i++) {
    fdct->divisors[i] = NULL;
#ifdef DCT_FLOAT_SUPPORTED
    fdct->float_divisors[i] = NULL;
#endif
  }
}