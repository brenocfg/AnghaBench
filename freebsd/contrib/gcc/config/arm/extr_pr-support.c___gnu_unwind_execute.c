#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int _uw ;
typedef  int /*<<< orphan*/  __gnu_unwind_state ;
typedef  int /*<<< orphan*/  _Unwind_Reason_Code ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 int CODE_FINISH ; 
 int R_LR ; 
 int R_PC ; 
 int R_SP ; 
 int /*<<< orphan*/  _URC_FAILURE ; 
 int /*<<< orphan*/  _URC_OK ; 
 int /*<<< orphan*/  _UVRSC_CORE ; 
 int /*<<< orphan*/  _UVRSC_FPA ; 
 int /*<<< orphan*/  _UVRSC_VFP ; 
 int /*<<< orphan*/  _UVRSC_WMMXC ; 
 int /*<<< orphan*/  _UVRSC_WMMXD ; 
 int /*<<< orphan*/  _UVRSD_DOUBLE ; 
 int /*<<< orphan*/  _UVRSD_FPAX ; 
 int /*<<< orphan*/  _UVRSD_UINT32 ; 
 int /*<<< orphan*/  _UVRSD_UINT64 ; 
 int /*<<< orphan*/  _UVRSD_VFPX ; 
 scalar_t__ _UVRSR_OK ; 
 int /*<<< orphan*/  _Unwind_VRS_Get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ _Unwind_VRS_Pop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _Unwind_VRS_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int next_unwind_byte (int /*<<< orphan*/ *) ; 

_Unwind_Reason_Code
__gnu_unwind_execute (_Unwind_Context * context, __gnu_unwind_state * uws)
{
  _uw op;
  int set_pc;
  _uw reg;

  set_pc = 0;
  for (;;)
    {
      op = next_unwind_byte (uws);
      if (op == CODE_FINISH)
	{
	  /* If we haven't already set pc then copy it from lr.  */
	  if (!set_pc)
	    {
	      _Unwind_VRS_Get (context, _UVRSC_CORE, R_LR, _UVRSD_UINT32,
			       &reg);
	      _Unwind_VRS_Set (context, _UVRSC_CORE, R_PC, _UVRSD_UINT32,
			       &reg);
	      set_pc = 1;
	    }
	  /* Drop out of the loop.  */
	  break;
	}
      if ((op & 0x80) == 0)
	{
	  /* vsp = vsp +- (imm6 << 2 + 4).  */
	  _uw offset;

	  offset = ((op & 0x3f) << 2) + 4;
	  _Unwind_VRS_Get (context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
	  if (op & 0x40)
	    reg -= offset;
	  else
	    reg += offset;
	  _Unwind_VRS_Set (context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
	  continue;
	}
      
      if ((op & 0xf0) == 0x80)
	{
	  op = (op << 8) | next_unwind_byte (uws);
	  if (op == 0x8000)
	    {
	      /* Refuse to unwind.  */
	      return _URC_FAILURE;
	    }
	  /* Pop r4-r15 under mask.  */
	  op = (op << 4) & 0xfff0;
	  if (_Unwind_VRS_Pop (context, _UVRSC_CORE, op, _UVRSD_UINT32)
	      != _UVRSR_OK)
	    return _URC_FAILURE;
	  if (op & (1 << R_PC))
	    set_pc = 1;
	  continue;
	}
      if ((op & 0xf0) == 0x90)
	{
	  op &= 0xf;
	  if (op == 13 || op == 15)
	    /* Reserved.  */
	    return _URC_FAILURE;
	  /* vsp = r[nnnn].  */
	  _Unwind_VRS_Get (context, _UVRSC_CORE, op, _UVRSD_UINT32, &reg);
	  _Unwind_VRS_Set (context, _UVRSC_CORE, R_SP, _UVRSD_UINT32, &reg);
	  continue;
	}
      if ((op & 0xf0) == 0xa0)
	{
	  /* Pop r4-r[4+nnn], [lr].  */
	  _uw mask;
	  
	  mask = (0xff0 >> (7 - (op & 7))) & 0xff0;
	  if (op & 8)
	    mask |= (1 << R_LR);
	  if (_Unwind_VRS_Pop (context, _UVRSC_CORE, mask, _UVRSD_UINT32)
	      != _UVRSR_OK)
	    return _URC_FAILURE;
	  continue;
	}
      if ((op & 0xf0) == 0xb0)
	{
	  /* op == 0xb0 already handled.  */
	  if (op == 0xb1)
	    {
	      op = next_unwind_byte (uws);
	      if (op == 0 || ((op & 0xf0) != 0))
		/* Spare.  */
		return _URC_FAILURE;
	      /* Pop r0-r4 under mask.  */
	      if (_Unwind_VRS_Pop (context, _UVRSC_CORE, op, _UVRSD_UINT32)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  if (op == 0xb2)
	    {
	      /* vsp = vsp + 0x204 + (uleb128 << 2).  */
	      int shift;

	      _Unwind_VRS_Get (context, _UVRSC_CORE, R_SP, _UVRSD_UINT32,
			       &reg);
	      op = next_unwind_byte (uws);
	      shift = 2;
	      while (op & 0x80)
		{
		  reg += ((op & 0x7f) << shift);
		  shift += 7;
		  op = next_unwind_byte (uws);
		}
	      reg += ((op & 0x7f) << shift) + 0x204;
	      _Unwind_VRS_Set (context, _UVRSC_CORE, R_SP, _UVRSD_UINT32,
			       &reg);
	      continue;
	    }
	  if (op == 0xb3)
	    {
	      /* Pop VFP registers with fldmx.  */
	      op = next_unwind_byte (uws);
	      op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
	      if (_Unwind_VRS_Pop (context, _UVRSC_VFP, op, _UVRSD_VFPX)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  if ((op & 0xfc) == 0xb4)
	    {
	      /* Pop FPA E[4]-E[4+nn].  */
	      op = 0x40000 | ((op & 3) + 1);
	      if (_Unwind_VRS_Pop (context, _UVRSC_FPA, op, _UVRSD_FPAX)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  /* op & 0xf8 == 0xb8.  */
	  /* Pop VFP D[8]-D[8+nnn] with fldmx.  */
	  op = 0x80000 | ((op & 7) + 1);
	  if (_Unwind_VRS_Pop (context, _UVRSC_VFP, op, _UVRSD_VFPX)
	      != _UVRSR_OK)
	    return _URC_FAILURE;
	  continue;
	}
      if ((op & 0xf0) == 0xc0)
	{
	  if (op == 0xc6)
	    {
	      /* Pop iWMMXt D registers.  */
	      op = next_unwind_byte (uws);
	      op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
	      if (_Unwind_VRS_Pop (context, _UVRSC_WMMXD, op, _UVRSD_UINT64)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  if (op == 0xc7)
	    {
	      op = next_unwind_byte (uws);
	      if (op == 0 || (op & 0xf0) != 0)
		/* Spare.  */
		return _URC_FAILURE;
	      /* Pop iWMMXt wCGR{3,2,1,0} under mask.  */
	      if (_Unwind_VRS_Pop (context, _UVRSC_WMMXC, op, _UVRSD_UINT32)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  if ((op & 0xf8) == 0xc0)
	    {
	      /* Pop iWMMXt wR[10]-wR[10+nnn].  */
	      op = 0xa0000 | ((op & 0xf) + 1);
	      if (_Unwind_VRS_Pop (context, _UVRSC_WMMXD, op, _UVRSD_UINT64)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  if (op == 0xc8)
	    {
	      /* Pop FPA registers.  */
	      op = next_unwind_byte (uws);
	      op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
	      if (_Unwind_VRS_Pop (context, _UVRSC_FPA, op, _UVRSD_FPAX)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  if (op == 0xc9)
	    {
	      /* Pop VFP registers with fldmd.  */
	      op = next_unwind_byte (uws);
	      op = ((op & 0xf0) << 12) | ((op & 0xf) + 1);
	      if (_Unwind_VRS_Pop (context, _UVRSC_VFP, op, _UVRSD_DOUBLE)
		  != _UVRSR_OK)
		return _URC_FAILURE;
	      continue;
	    }
	  /* Spare.  */
	  return _URC_FAILURE;
	}
      if ((op & 0xf8) == 0xd0)
	{
	  /* Pop VFP D[8]-D[8+nnn] with fldmd.  */
	  op = 0x80000 | ((op & 7) + 1);
	  if (_Unwind_VRS_Pop (context, _UVRSC_VFP, op, _UVRSD_DOUBLE)
	      != _UVRSR_OK)
	    return _URC_FAILURE;
	  continue;
	}
      /* Spare.  */
      return _URC_FAILURE;
    }
  return _URC_OK;
}