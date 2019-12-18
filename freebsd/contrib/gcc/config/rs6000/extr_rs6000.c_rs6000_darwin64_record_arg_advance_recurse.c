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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_6__ {int fregno; int words; int intoffset; int /*<<< orphan*/  vregno; } ;
typedef  int HOST_WIDE_INT ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 scalar_t__ DECL_SIZE (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int TYPE_MODE (scalar_t__) ; 
 scalar_t__ USE_ALTIVEC_FOR_ARG_P (TYPE_1__*,int,scalar_t__,int) ; 
 scalar_t__ USE_FP_FOR_ARG_P (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  bit_position (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ int_bit_position (scalar_t__) ; 
 int /*<<< orphan*/  rs6000_darwin64_record_arg_advance_flush (TYPE_1__*,int) ; 

__attribute__((used)) static void
rs6000_darwin64_record_arg_advance_recurse (CUMULATIVE_ARGS *cum,
					    tree type,
					    HOST_WIDE_INT startbitpos)
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
	  rs6000_darwin64_record_arg_advance_recurse (cum, ftype, bitpos);
	else if (USE_FP_FOR_ARG_P (cum, mode, ftype))
	  {
	    rs6000_darwin64_record_arg_advance_flush (cum, bitpos);
	    cum->fregno += (GET_MODE_SIZE (mode) + 7) >> 3;
	    cum->words += (GET_MODE_SIZE (mode) + 7) >> 3;
	  }
	else if (USE_ALTIVEC_FOR_ARG_P (cum, mode, type, 1))
	  {
	    rs6000_darwin64_record_arg_advance_flush (cum, bitpos);
	    cum->vregno++;
	    cum->words += 2;
	  }
	else if (cum->intoffset == -1)
	  cum->intoffset = bitpos;
      }
}