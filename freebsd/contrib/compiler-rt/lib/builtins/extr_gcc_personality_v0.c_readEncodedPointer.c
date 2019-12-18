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
typedef  int uint8_t ;
typedef  uintptr_t uint64_t ;
typedef  uintptr_t uint32_t ;
typedef  uintptr_t uint16_t ;
typedef  uintptr_t int64_t ;
typedef  uintptr_t int32_t ;
typedef  uintptr_t int16_t ;

/* Variables and functions */
#define  DW_EH_PE_absptr 141 
#define  DW_EH_PE_aligned 140 
#define  DW_EH_PE_datarel 139 
#define  DW_EH_PE_funcrel 138 
 int DW_EH_PE_indirect ; 
 int DW_EH_PE_omit ; 
#define  DW_EH_PE_pcrel 137 
#define  DW_EH_PE_sdata2 136 
#define  DW_EH_PE_sdata4 135 
#define  DW_EH_PE_sdata8 134 
#define  DW_EH_PE_sleb128 133 
#define  DW_EH_PE_textrel 132 
#define  DW_EH_PE_udata2 131 
#define  DW_EH_PE_udata4 130 
#define  DW_EH_PE_udata8 129 
#define  DW_EH_PE_uleb128 128 
 int /*<<< orphan*/  compilerrt_abort () ; 
 uintptr_t readULEB128 (int const**) ; 

__attribute__((used)) static uintptr_t readEncodedPointer(const uint8_t **data, uint8_t encoding) {
  const uint8_t *p = *data;
  uintptr_t result = 0;

  if (encoding == DW_EH_PE_omit)
    return 0;

  // first get value
  switch (encoding & 0x0F) {
  case DW_EH_PE_absptr:
    result = *((const uintptr_t *)p);
    p += sizeof(uintptr_t);
    break;
  case DW_EH_PE_uleb128:
    result = readULEB128(&p);
    break;
  case DW_EH_PE_udata2:
    result = *((const uint16_t *)p);
    p += sizeof(uint16_t);
    break;
  case DW_EH_PE_udata4:
    result = *((const uint32_t *)p);
    p += sizeof(uint32_t);
    break;
  case DW_EH_PE_udata8:
    result = *((const uint64_t *)p);
    p += sizeof(uint64_t);
    break;
  case DW_EH_PE_sdata2:
    result = *((const int16_t *)p);
    p += sizeof(int16_t);
    break;
  case DW_EH_PE_sdata4:
    result = *((const int32_t *)p);
    p += sizeof(int32_t);
    break;
  case DW_EH_PE_sdata8:
    result = *((const int64_t *)p);
    p += sizeof(int64_t);
    break;
  case DW_EH_PE_sleb128:
  default:
    // not supported
    compilerrt_abort();
    break;
  }

  // then add relative offset
  switch (encoding & 0x70) {
  case DW_EH_PE_absptr:
    // do nothing
    break;
  case DW_EH_PE_pcrel:
    result += (uintptr_t)(*data);
    break;
  case DW_EH_PE_textrel:
  case DW_EH_PE_datarel:
  case DW_EH_PE_funcrel:
  case DW_EH_PE_aligned:
  default:
    // not supported
    compilerrt_abort();
    break;
  }

  // then apply indirection
  if (encoding & DW_EH_PE_indirect) {
    result = *((const uintptr_t *)result);
  }

  *data = p;
  return result;
}