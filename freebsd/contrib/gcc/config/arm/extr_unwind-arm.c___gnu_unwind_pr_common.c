#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type_info ;
typedef  int _uw ;
struct TYPE_15__ {int data; int* next; int words_left; int bytes_left; } ;
typedef  TYPE_4__ __gnu_unwind_state ;
typedef  int _Unwind_State ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;
struct TYPE_14__ {int sp; int* bitpattern; } ;
struct TYPE_13__ {int* bitpattern; } ;
struct TYPE_12__ {int additional; int fnstart; scalar_t__ ehtp; } ;
struct TYPE_16__ {TYPE_3__ barrier_cache; TYPE_2__ cleanup_cache; TYPE_1__ pr_cache; } ;
typedef  TYPE_5__ _Unwind_Control_Block ;
typedef  int /*<<< orphan*/  _Unwind_Context ;
struct TYPE_18__ {int length; int offset; } ;
struct TYPE_17__ {int length; int offset; } ;
typedef  TYPE_6__ EHT32 ;
typedef  TYPE_7__ EHT16 ;

/* Variables and functions */
 int /*<<< orphan*/  R_LR ; 
 int /*<<< orphan*/  R_PC ; 
 int /*<<< orphan*/  R_SP ; 
 int /*<<< orphan*/  _URC_CONTINUE_UNWIND ; 
 int /*<<< orphan*/  _URC_FAILURE ; 
 int /*<<< orphan*/  _URC_HANDLER_FOUND ; 
 int /*<<< orphan*/  _URC_INSTALL_CONTEXT ; 
 scalar_t__ _URC_OK ; 
 int _US_ACTION_MASK ; 
 int _US_FORCE_UNWIND ; 
 int _US_UNWIND_FRAME_RESUME ; 
 int _US_VIRTUAL_UNWIND_FRAME ; 
 int _Unwind_GetGR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _Unwind_SetGR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int _Unwind_decode_target2 (int) ; 
 int /*<<< orphan*/  __cxa_begin_cleanup (TYPE_5__*) ; 
 int /*<<< orphan*/  __cxa_call_unexpected ; 
 int /*<<< orphan*/  __cxa_type_match (TYPE_5__*,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ __gnu_unwind_execute (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int selfrel_offset31 (int*) ; 
 int uint32_highbit ; 

__attribute__((used)) static _Unwind_Reason_Code
__gnu_unwind_pr_common (_Unwind_State state,
			_Unwind_Control_Block *ucbp,
			_Unwind_Context *context,
			int id)
{
  __gnu_unwind_state uws;
  _uw *data;
  _uw offset;
  _uw len;
  _uw rtti_count;
  int phase2_call_unexpected_after_unwind = 0;
  int in_range = 0;
  int forced_unwind = state & _US_FORCE_UNWIND;

  state &= _US_ACTION_MASK;

  data = (_uw *) ucbp->pr_cache.ehtp;
  uws.data = *(data++);
  uws.next = data;
  if (id == 0)
    {
      uws.data <<= 8;
      uws.words_left = 0;
      uws.bytes_left = 3;
    }
  else
    {
      uws.words_left = (uws.data >> 16) & 0xff;
      uws.data <<= 16;
      uws.bytes_left = 2;
      data += uws.words_left;
    }

  /* Restore the saved pointer.  */
  if (state == _US_UNWIND_FRAME_RESUME)
    data = (_uw *) ucbp->cleanup_cache.bitpattern[0];

  if ((ucbp->pr_cache.additional & 1) == 0)
    {
      /* Process descriptors.  */
      while (*data)
	{
	  _uw addr;
	  _uw fnstart;

	  if (id == 2)
	    {
	      len = ((EHT32 *) data)->length;
	      offset = ((EHT32 *) data)->offset;
	      data += 2;
	    }
	  else
	    {
	      len = ((EHT16 *) data)->length;
	      offset = ((EHT16 *) data)->offset;
	      data++;
	    }

	  fnstart = ucbp->pr_cache.fnstart + (offset & ~1);
	  addr = _Unwind_GetGR (context, R_PC);
	  in_range = (fnstart <= addr && addr < fnstart + (len & ~1));

	  switch (((offset & 1) << 1) | (len & 1))
	    {
	    case 0:
	      /* Cleanup.  */
	      if (state != _US_VIRTUAL_UNWIND_FRAME
		  && in_range)
		{
		  /* Cleanup in range, and we are running cleanups.  */
		  _uw lp;

		  /* Landing pad address is 31-bit pc-relative offset.  */
		  lp = selfrel_offset31 (data);
		  data++;
		  /* Save the exception data pointer.  */
		  ucbp->cleanup_cache.bitpattern[0] = (_uw) data;
		  if (!__cxa_begin_cleanup (ucbp))
		    return _URC_FAILURE;
		  /* Setup the VRS to enter the landing pad.  */
		  _Unwind_SetGR (context, R_PC, lp);
		  return _URC_INSTALL_CONTEXT;
		}
	      /* Cleanup not in range, or we are in stage 1.  */
	      data++;
	      break;

	    case 1:
	      /* Catch handler.  */
	      if (state == _US_VIRTUAL_UNWIND_FRAME)
		{
		  if (in_range)
		    {
		      /* Check for a barrier.  */
		      _uw rtti;
		      void *matched;

		      /* Check for no-throw areas.  */
		      if (data[1] == (_uw) -2)
			return _URC_FAILURE;

		      /* The thrown object immediately follows the ECB.  */
		      matched = (void *)(ucbp + 1);
		      if (data[1] != (_uw) -1)
			{
			  /* Match a catch specification.  */
			  rtti = _Unwind_decode_target2 ((_uw) &data[1]);
			  if (!__cxa_type_match (ucbp, (type_info *) rtti,
						 &matched))
			    matched = (void *)0;
			}

		      if (matched)
			{
			  ucbp->barrier_cache.sp =
			    _Unwind_GetGR (context, R_SP);
			  ucbp->barrier_cache.bitpattern[0] = (_uw) matched;
			  ucbp->barrier_cache.bitpattern[1] = (_uw) data;
			  return _URC_HANDLER_FOUND;
			}
		    }
		  /* Handler out of range, or not matched.  */
		}
	      else if (ucbp->barrier_cache.sp == _Unwind_GetGR (context, R_SP)
		       && ucbp->barrier_cache.bitpattern[1] == (_uw) data)
		{
		  /* Matched a previous propagation barrier.  */
		  _uw lp;

		  /* Setup for entry to the handler.  */
		  lp = selfrel_offset31 (data);
		  _Unwind_SetGR (context, R_PC, lp);
		  _Unwind_SetGR (context, 0, (_uw) ucbp);
		  return _URC_INSTALL_CONTEXT;
		}
	      /* Catch handler not matched.  Advance to the next descriptor.  */
	      data += 2;
	      break;

	    case 2:
	      rtti_count = data[0] & 0x7fffffff;
	      /* Exception specification.  */
	      if (state == _US_VIRTUAL_UNWIND_FRAME)
		{
		  if (in_range && (!forced_unwind || !rtti_count))
		    {
		      /* Match against the exception specification.  */
		      _uw i;
		      _uw rtti;
		      void *matched;

		      for (i = 0; i < rtti_count; i++)
			{
			  matched = (void *)(ucbp + 1);
			  rtti = _Unwind_decode_target2 ((_uw) &data[i + 1]);
			  if (__cxa_type_match (ucbp, (type_info *) rtti,
						&matched))
			    break;
			}

		      if (i == rtti_count)
			{
			  /* Exception does not match the spec.  */
			  ucbp->barrier_cache.sp =
			    _Unwind_GetGR (context, R_SP);
			  ucbp->barrier_cache.bitpattern[0] = (_uw) matched;
			  ucbp->barrier_cache.bitpattern[1] = (_uw) data;
			  return _URC_HANDLER_FOUND;
			}
		    }
		  /* Handler out of range, or exception is permitted.  */
		}
	      else if (ucbp->barrier_cache.sp == _Unwind_GetGR (context, R_SP)
		       && ucbp->barrier_cache.bitpattern[1] == (_uw) data)
		{
		  /* Matched a previous propagation barrier.  */
		  _uw lp;
		  /* Record the RTTI list for __cxa_call_unexpected.  */
		  ucbp->barrier_cache.bitpattern[1] = rtti_count;
		  ucbp->barrier_cache.bitpattern[2] = 0;
		  ucbp->barrier_cache.bitpattern[3] = 4;
		  ucbp->barrier_cache.bitpattern[4] = (_uw) &data[1];

		  if (data[0] & uint32_highbit)
		    phase2_call_unexpected_after_unwind = 1;
		  else
		    {
		      data += rtti_count + 1;
		      /* Setup for entry to the handler.  */
		      lp = selfrel_offset31 (data);
		      data++;
		      _Unwind_SetGR (context, R_PC, lp);
		      _Unwind_SetGR (context, 0, (_uw) ucbp);
		      return _URC_INSTALL_CONTEXT;
		    }
		}
	      if (data[0] & uint32_highbit)
		data++;
	      data += rtti_count + 1;
	      break;

	    default:
	      /* Should never happen.  */
	      return _URC_FAILURE;
	    }
	  /* Finished processing this descriptor.  */
	}
    }

  if (__gnu_unwind_execute (context, &uws) != _URC_OK)
    return _URC_FAILURE;

  if (phase2_call_unexpected_after_unwind)
    {
      /* Enter __cxa_unexpected as if called from the call site.  */
      _Unwind_SetGR (context, R_LR, _Unwind_GetGR (context, R_PC));
      _Unwind_SetGR (context, R_PC, (_uw) &__cxa_call_unexpected);
      return _URC_INSTALL_CONTEXT;
    }

  return _URC_CONTINUE_UNWIND;
}