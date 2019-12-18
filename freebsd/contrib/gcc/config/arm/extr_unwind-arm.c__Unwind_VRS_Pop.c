#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfp_regs {int /*<<< orphan*/ * d; } ;
struct TYPE_3__ {int* r; } ;
struct TYPE_4__ {int demand_save_flags; TYPE_1__ core; struct vfp_regs vfp; } ;
typedef  TYPE_2__ phase1_vrs ;
typedef  int _uw ;
typedef  int /*<<< orphan*/  _Unwind_VRS_Result ;
typedef  int _Unwind_VRS_RegClass ;
typedef  int /*<<< orphan*/  _Unwind_VRS_DataRepresentation ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
 int DEMAND_SAVE_VFP ; 
 size_t R_SP ; 
#define  _UVRSC_CORE 132 
#define  _UVRSC_FPA 131 
#define  _UVRSC_VFP 130 
#define  _UVRSC_WMMXC 129 
#define  _UVRSC_WMMXD 128 
 int /*<<< orphan*/  _UVRSD_DOUBLE ; 
 int /*<<< orphan*/  _UVRSD_UINT32 ; 
 int /*<<< orphan*/  _UVRSD_VFPX ; 
 int /*<<< orphan*/  _UVRSR_FAILED ; 
 int /*<<< orphan*/  _UVRSR_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  _UVRSR_OK ; 
 int /*<<< orphan*/  __gnu_Unwind_Restore_VFP (struct vfp_regs*) ; 
 int /*<<< orphan*/  __gnu_Unwind_Save_VFP (struct vfp_regs*) ; 

_Unwind_VRS_Result _Unwind_VRS_Pop (_Unwind_Context *context,
				    _Unwind_VRS_RegClass regclass,
				    _uw discriminator,
				    _Unwind_VRS_DataRepresentation representation)
{
  phase1_vrs *vrs = (phase1_vrs *) context;

  switch (regclass)
    {
    case _UVRSC_CORE:
      {
	_uw *ptr;
	_uw mask;
	int i;

	if (representation != _UVRSD_UINT32)
	  return _UVRSR_FAILED;

	mask = discriminator & 0xffff;
	ptr = (_uw *) vrs->core.r[R_SP];
	/* Pop the requested registers.  */
	for (i = 0; i < 16; i++)
	  {
	    if (mask & (1 << i))
	      vrs->core.r[i] = *(ptr++);
	  }
	/* Writeback the stack pointer value if it wasn't restored.  */
	if ((mask & (1 << R_SP)) == 0)
	  vrs->core.r[R_SP] = (_uw) ptr;
      }
      return _UVRSR_OK;

    case _UVRSC_VFP:
      {
	_uw start = discriminator >> 16;
	_uw count = discriminator & 0xffff;
	struct vfp_regs tmp;
	_uw *sp;
	_uw *dest;

	if ((representation != _UVRSD_VFPX && representation != _UVRSD_DOUBLE)
	    || start + count > 16)
	  return _UVRSR_FAILED;

	if (vrs->demand_save_flags & DEMAND_SAVE_VFP)
	  {
	    /* Demand-save resisters for stage1.  */
	    vrs->demand_save_flags &= ~DEMAND_SAVE_VFP;
	    __gnu_Unwind_Save_VFP (&vrs->vfp);
	  }

	/* Restore the registers from the stack.  Do this by saving the
	   current VFP registers to a memory area, moving the in-memory
	   values into that area, and restoring from the whole area.
	   For _UVRSD_VFPX we assume FSTMX standard format 1.  */
	__gnu_Unwind_Save_VFP (&tmp);

	/* The stack address is only guaranteed to be word aligned, so
	   we can't use doubleword copies.  */
	sp = (_uw *) vrs->core.r[R_SP];
	dest = (_uw *) &tmp.d[start];
	count *= 2;
	while (count--)
	  *(dest++) = *(sp++);

	/* Skip the pad word */
	if (representation == _UVRSD_VFPX)
	  sp++;

	/* Set the new stack pointer.  */
	vrs->core.r[R_SP] = (_uw) sp;

	/* Reload the registers.  */
	__gnu_Unwind_Restore_VFP (&tmp);
      }
      return _UVRSR_OK;

    case _UVRSC_FPA:
    case _UVRSC_WMMXD:
    case _UVRSC_WMMXC:
      return _UVRSR_NOT_IMPLEMENTED;

    default:
      return _UVRSR_FAILED;
    }
}