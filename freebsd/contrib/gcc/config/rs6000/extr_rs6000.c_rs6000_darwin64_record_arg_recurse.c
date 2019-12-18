#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {int intoffset; int /*<<< orphan*/  vregno; scalar_t__ named; int /*<<< orphan*/  fregno; } ;
typedef  int HOST_WIDE_INT ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
#define  DCmode 130 
 scalar_t__ DECL_SIZE (scalar_t__) ; 
 int DFmode ; 
 scalar_t__ FIELD_DECL ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ RECORD_TYPE ; 
#define  SCmode 129 
 int SFmode ; 
#define  TCmode 128 
 int TFmode ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int TYPE_MODE (scalar_t__) ; 
 scalar_t__ USE_ALTIVEC_FOR_ARG_P (TYPE_1__*,int,scalar_t__,int) ; 
 scalar_t__ USE_FP_FOR_ARG_P (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  bit_position (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ int_bit_position (scalar_t__) ; 
 int /*<<< orphan*/  rs6000_darwin64_record_arg_flush (TYPE_1__*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
rs6000_darwin64_record_arg_recurse (CUMULATIVE_ARGS *cum, tree type,
				    HOST_WIDE_INT startbitpos, rtx rvec[],
				    int *k)
{
  tree f;

  for (f = TYPE_FIELDS (type); f ; f = TREE_CHAIN (f))
    if (TREE_CODE (f) == FIELD_DECL)
      {
	HOST_WIDE_INT bitpos = startbitpos;
	tree ftype = TREE_TYPE (f);
	enum machine_mode mode;
	if (ftype == error_mark_node)
	  continue;
	mode = TYPE_MODE (ftype);

	if (DECL_SIZE (f) != 0
	    && host_integerp (bit_position (f), 1))
	  bitpos += int_bit_position (f);

	/* ??? FIXME: else assume zero offset.  */

	if (TREE_CODE (ftype) == RECORD_TYPE)
	  rs6000_darwin64_record_arg_recurse (cum, ftype, bitpos, rvec, k);
	else if (cum->named && USE_FP_FOR_ARG_P (cum, mode, ftype))
	  {
#if 0
	    switch (mode)
	      {
	      case SCmode: mode = SFmode; break;
	      case DCmode: mode = DFmode; break;
	      case TCmode: mode = TFmode; break;
	      default: break;
	      }
#endif
	    rs6000_darwin64_record_arg_flush (cum, bitpos, rvec, k);
	    rvec[(*k)++]
	      = gen_rtx_EXPR_LIST (VOIDmode,
				   gen_rtx_REG (mode, cum->fregno++),
				   GEN_INT (bitpos / BITS_PER_UNIT));
	    if (mode == TFmode)
	      cum->fregno++;
	  }
	else if (cum->named && USE_ALTIVEC_FOR_ARG_P (cum, mode, ftype, 1))
	  {
	    rs6000_darwin64_record_arg_flush (cum, bitpos, rvec, k);
	    rvec[(*k)++]
	      = gen_rtx_EXPR_LIST (VOIDmode,
				   gen_rtx_REG (mode, cum->vregno++),
				   GEN_INT (bitpos / BITS_PER_UNIT));
	  }
	else if (cum->intoffset == -1)
	  cum->intoffset = bitpos;
      }
}