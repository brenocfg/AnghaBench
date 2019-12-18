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

/* Variables and functions */
#define  DT_DLT 151 
#define  DT_DLT_SIZE 150 
#define  DT_HP_BIND_NOW_COUNT 149 
#define  DT_HP_CHECKSUM 148 
#define  DT_HP_COMPAT_FILTERED 147 
#define  DT_HP_DLD_FLAGS 146 
#define  DT_HP_DLD_HOOK 145 
#define  DT_HP_EPLTREL 144 
#define  DT_HP_EPLTRELSZ 143 
#define  DT_HP_FILTERED 142 
#define  DT_HP_FILTER_TLS 141 
#define  DT_HP_GST_HASHVAL 140 
#define  DT_HP_GST_SIZE 139 
#define  DT_HP_GST_VERSION 138 
#define  DT_HP_LAZYLOAD 137 
#define  DT_HP_LOAD_MAP 136 
#define  DT_HP_NEEDED 135 
#define  DT_HP_PREINIT 134 
#define  DT_HP_PREINITSZ 133 
#define  DT_HP_TIME_STAMP 132 
#define  DT_HP_UX10_INIT 131 
#define  DT_HP_UX10_INITSZ 130 
#define  DT_PLT 129 
#define  DT_PLT_SIZE 128 

__attribute__((used)) static const char *
get_parisc_dynamic_type (unsigned long type)
{
  switch (type)
    {
    case DT_HP_LOAD_MAP:	return "HP_LOAD_MAP";
    case DT_HP_DLD_FLAGS:	return "HP_DLD_FLAGS";
    case DT_HP_DLD_HOOK:	return "HP_DLD_HOOK";
    case DT_HP_UX10_INIT:	return "HP_UX10_INIT";
    case DT_HP_UX10_INITSZ:	return "HP_UX10_INITSZ";
    case DT_HP_PREINIT:		return "HP_PREINIT";
    case DT_HP_PREINITSZ:	return "HP_PREINITSZ";
    case DT_HP_NEEDED:		return "HP_NEEDED";
    case DT_HP_TIME_STAMP:	return "HP_TIME_STAMP";
    case DT_HP_CHECKSUM:	return "HP_CHECKSUM";
    case DT_HP_GST_SIZE:	return "HP_GST_SIZE";
    case DT_HP_GST_VERSION:	return "HP_GST_VERSION";
    case DT_HP_GST_HASHVAL:	return "HP_GST_HASHVAL";
    case DT_HP_EPLTREL:		return "HP_GST_EPLTREL";
    case DT_HP_EPLTRELSZ:	return "HP_GST_EPLTRELSZ";
    case DT_HP_FILTERED:	return "HP_FILTERED";
    case DT_HP_FILTER_TLS:	return "HP_FILTER_TLS";
    case DT_HP_COMPAT_FILTERED:	return "HP_COMPAT_FILTERED";
    case DT_HP_LAZYLOAD:	return "HP_LAZYLOAD";
    case DT_HP_BIND_NOW_COUNT:	return "HP_BIND_NOW_COUNT";
    case DT_PLT:		return "PLT";
    case DT_PLT_SIZE:		return "PLT_SIZE";
    case DT_DLT:		return "DLT";
    case DT_DLT_SIZE:		return "DLT_SIZE";
    default:
      return NULL;
    }
}