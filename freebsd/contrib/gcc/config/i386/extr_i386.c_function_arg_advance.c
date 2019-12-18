#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {int words; int nregs; int sse_nregs; int regno; int sse_regno; int float_in_sse; int sse_words; int mmx_words; int mmx_nregs; int mmx_regno; } ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int /*<<< orphan*/  AGGREGATE_TYPE_P (scalar_t__) ; 
#define  BLKmode 145 
#define  DFmode 144 
#define  DImode 143 
 char* GET_MODE_NAME (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
#define  HImode 142 
#define  QImode 141 
#define  SFmode 140 
#define  SImode 139 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_DEBUG_ARG ; 
#define  TImode 138 
 int UNITS_PER_WORD ; 
#define  V16QImode 137 
#define  V2DFmode 136 
#define  V2DImode 135 
#define  V2SFmode 134 
#define  V2SImode 133 
#define  V4HImode 132 
#define  V4SFmode 131 
#define  V4SImode 130 
#define  V8HImode 129 
#define  V8QImode 128 
 int /*<<< orphan*/  examine_argument (int,scalar_t__,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,char*,int) ; 
 int int_size_in_bytes (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int type_natural_mode (scalar_t__) ; 

void
function_arg_advance (CUMULATIVE_ARGS *cum, enum machine_mode mode,
		      tree type, int named)
{
  int bytes =
    (mode == BLKmode) ? int_size_in_bytes (type) : (int) GET_MODE_SIZE (mode);
  int words = (bytes + UNITS_PER_WORD - 1) / UNITS_PER_WORD;

  if (type)
    mode = type_natural_mode (type);

  if (TARGET_DEBUG_ARG)
    fprintf (stderr, "function_adv (sz=%d, wds=%2d, nregs=%d, ssenregs=%d, "
	     "mode=%s, named=%d)\n\n",
	     words, cum->words, cum->nregs, cum->sse_nregs,
	     GET_MODE_NAME (mode), named);

  if (TARGET_64BIT)
    {
      int int_nregs, sse_nregs;
      if (!examine_argument (mode, type, 0, &int_nregs, &sse_nregs))
	cum->words += words;
      else if (sse_nregs <= cum->sse_nregs && int_nregs <= cum->nregs)
	{
	  cum->nregs -= int_nregs;
	  cum->sse_nregs -= sse_nregs;
	  cum->regno += int_nregs;
	  cum->sse_regno += sse_nregs;
	}
      else
	cum->words += words;
    }
  else
    {
      switch (mode)
	{
	default:
	  break;

	case BLKmode:
	  if (bytes < 0)
	    break;
	  /* FALLTHRU */

	case DImode:
	case SImode:
	case HImode:
	case QImode:
	  cum->words += words;
	  cum->nregs -= words;
	  cum->regno += words;

	  if (cum->nregs <= 0)
	    {
	      cum->nregs = 0;
	      cum->regno = 0;
	    }
	  break;

	case DFmode:
	  if (cum->float_in_sse < 2)
	    break;
	case SFmode:
	  if (cum->float_in_sse < 1)
	    break;
	  /* FALLTHRU */

	case TImode:
	case V16QImode:
	case V8HImode:
	case V4SImode:
	case V2DImode:
	case V4SFmode:
	case V2DFmode:
	  if (!type || !AGGREGATE_TYPE_P (type))
	    {
	      cum->sse_words += words;
	      cum->sse_nregs -= 1;
	      cum->sse_regno += 1;
	      if (cum->sse_nregs <= 0)
		{
		  cum->sse_nregs = 0;
		  cum->sse_regno = 0;
		}
	    }
	  break;

	case V8QImode:
	case V4HImode:
	case V2SImode:
	case V2SFmode:
	  if (!type || !AGGREGATE_TYPE_P (type))
	    {
	      cum->mmx_words += words;
	      cum->mmx_nregs -= 1;
	      cum->mmx_regno += 1;
	      if (cum->mmx_nregs <= 0)
		{
		  cum->mmx_nregs = 0;
		  cum->mmx_regno = 0;
		}
	    }
	  break;
	}
    }
}