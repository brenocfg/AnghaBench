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
struct _Unwind_Context {int dummy; } ;
typedef  int /*<<< orphan*/  _Unwind_Ptr ;

/* Variables and functions */
#define  DW_EH_PE_absptr 133 
#define  DW_EH_PE_aligned 132 
#define  DW_EH_PE_datarel 131 
#define  DW_EH_PE_funcrel 130 
 unsigned char DW_EH_PE_omit ; 
#define  DW_EH_PE_pcrel 129 
#define  DW_EH_PE_textrel 128 
 int /*<<< orphan*/  _Unwind_GetDataRelBase (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  _Unwind_GetRegionStart (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  _Unwind_GetTextRelBase (struct _Unwind_Context*) ; 
 int /*<<< orphan*/  __gxx_abort () ; 

__attribute__((used)) static _Unwind_Ptr
base_of_encoded_value (unsigned char encoding, struct _Unwind_Context *context)
{
  if (encoding == DW_EH_PE_omit)
    return 0;

  switch (encoding & 0x70)
    {
    case DW_EH_PE_absptr:
    case DW_EH_PE_pcrel:
    case DW_EH_PE_aligned:
      return 0;

    case DW_EH_PE_textrel:
      return _Unwind_GetTextRelBase (context);
    case DW_EH_PE_datarel:
      return _Unwind_GetDataRelBase (context);
    case DW_EH_PE_funcrel:
      return _Unwind_GetRegionStart (context);
    }
  __gxx_abort ();
}