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
struct TYPE_3__ {int* r; } ;
struct TYPE_4__ {TYPE_1__ core; } ;
typedef  TYPE_2__ phase1_vrs ;
typedef  int _uw ;
typedef  int /*<<< orphan*/  _Unwind_VRS_Result ;
typedef  int _Unwind_VRS_RegClass ;
typedef  int /*<<< orphan*/  _Unwind_VRS_DataRepresentation ;
typedef  int /*<<< orphan*/  _Unwind_Context ;

/* Variables and functions */
#define  _UVRSC_CORE 132 
#define  _UVRSC_FPA 131 
#define  _UVRSC_VFP 130 
#define  _UVRSC_WMMXC 129 
#define  _UVRSC_WMMXD 128 
 int /*<<< orphan*/  _UVRSD_UINT32 ; 
 int /*<<< orphan*/  _UVRSR_FAILED ; 
 int /*<<< orphan*/  _UVRSR_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  _UVRSR_OK ; 

_Unwind_VRS_Result _Unwind_VRS_Get (_Unwind_Context *context,
				    _Unwind_VRS_RegClass regclass,
				    _uw regno,
				    _Unwind_VRS_DataRepresentation representation,
				    void *valuep)
{
  phase1_vrs *vrs = (phase1_vrs *) context;

  switch (regclass)
    {
    case _UVRSC_CORE:
      if (representation != _UVRSD_UINT32
	  || regno > 15)
	return _UVRSR_FAILED;
      *(_uw *) valuep = vrs->core.r[regno];
      return _UVRSR_OK;

    case _UVRSC_VFP:
    case _UVRSC_FPA:
    case _UVRSC_WMMXD:
    case _UVRSC_WMMXC:
      return _UVRSR_NOT_IMPLEMENTED;

    default:
      return _UVRSR_FAILED;
    }
}