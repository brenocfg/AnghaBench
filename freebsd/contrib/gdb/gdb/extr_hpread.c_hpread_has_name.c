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
typedef  enum dntt_entry_type { ____Placeholder_dntt_entry_type } dntt_entry_type ;

/* Variables and functions */
#define  DNTT_TYPE_ARRAY 180 
#define  DNTT_TYPE_BEGIN 179 
#define  DNTT_TYPE_BLOCKDATA 178 
#define  DNTT_TYPE_CLASS 177 
#define  DNTT_TYPE_CLASS_SCOPE 176 
#define  DNTT_TYPE_COBSTRUCT 175 
#define  DNTT_TYPE_COMMON 174 
#define  DNTT_TYPE_CONST 173 
#define  DNTT_TYPE_DOC_FUNCTION 172 
#define  DNTT_TYPE_DOC_MEMFUNC 171 
#define  DNTT_TYPE_DVAR 170 
#define  DNTT_TYPE_END 169 
#define  DNTT_TYPE_ENTRY 168 
#define  DNTT_TYPE_ENUM 167 
#define  DNTT_TYPE_FIELD 166 
#define  DNTT_TYPE_FILE 165 
#define  DNTT_TYPE_FPARAM 164 
#define  DNTT_TYPE_FRIEND_CLASS 163 
#define  DNTT_TYPE_FRIEND_FUNC 162 
#define  DNTT_TYPE_FUNCTION 161 
#define  DNTT_TYPE_FUNCTYPE 160 
#define  DNTT_TYPE_FUNC_TEMPLATE 159 
#define  DNTT_TYPE_GENFIELD 158 
#define  DNTT_TYPE_IMPORT 157 
#define  DNTT_TYPE_INHERITANCE 156 
#define  DNTT_TYPE_LABEL 155 
#define  DNTT_TYPE_LINK 154 
#define  DNTT_TYPE_MACRO 153 
#define  DNTT_TYPE_MEMACCESS 152 
#define  DNTT_TYPE_MEMENUM 151 
#define  DNTT_TYPE_MEMFUNC 150 
#define  DNTT_TYPE_MODIFIER 149 
#define  DNTT_TYPE_MODULE 148 
#define  DNTT_TYPE_OBJECT_ID 147 
#define  DNTT_TYPE_POINTER 146 
#define  DNTT_TYPE_PTRMEM 145 
#define  DNTT_TYPE_PTRMEMFUNC 144 
#define  DNTT_TYPE_REFERENCE 143 
#define  DNTT_TYPE_SA 142 
#define  DNTT_TYPE_SET 141 
#define  DNTT_TYPE_SRCFILE 140 
#define  DNTT_TYPE_STRUCT 139 
#define  DNTT_TYPE_SUBRANGE 138 
#define  DNTT_TYPE_SVAR 137 
#define  DNTT_TYPE_TAGDEF 136 
#define  DNTT_TYPE_TEMPLATE 135 
#define  DNTT_TYPE_TEMPLATE_ARG 134 
#define  DNTT_TYPE_TYPEDEF 133 
#define  DNTT_TYPE_UNION 132 
#define  DNTT_TYPE_VARIANT 131 
#define  DNTT_TYPE_VFUNC 130 
#define  DNTT_TYPE_WITH 129 
#define  DNTT_TYPE_XREF 128 

__attribute__((used)) static int
hpread_has_name (enum dntt_entry_type kind)
{
  switch (kind)
    {
    case DNTT_TYPE_SRCFILE:
    case DNTT_TYPE_MODULE:
    case DNTT_TYPE_FUNCTION:
    case DNTT_TYPE_DOC_FUNCTION:
    case DNTT_TYPE_ENTRY:
    case DNTT_TYPE_IMPORT:
    case DNTT_TYPE_LABEL:
    case DNTT_TYPE_FPARAM:
    case DNTT_TYPE_SVAR:
    case DNTT_TYPE_DVAR:
    case DNTT_TYPE_CONST:
    case DNTT_TYPE_TYPEDEF:
    case DNTT_TYPE_TAGDEF:
    case DNTT_TYPE_MEMENUM:
    case DNTT_TYPE_FIELD:
    case DNTT_TYPE_SA:
    case DNTT_TYPE_BLOCKDATA:
    case DNTT_TYPE_MEMFUNC:
    case DNTT_TYPE_DOC_MEMFUNC:
      return 1;

    case DNTT_TYPE_BEGIN:
    case DNTT_TYPE_END:
    case DNTT_TYPE_POINTER:
    case DNTT_TYPE_ENUM:
    case DNTT_TYPE_SET:
    case DNTT_TYPE_ARRAY:
    case DNTT_TYPE_STRUCT:
    case DNTT_TYPE_UNION:
    case DNTT_TYPE_VARIANT:
    case DNTT_TYPE_FILE:
    case DNTT_TYPE_FUNCTYPE:
    case DNTT_TYPE_SUBRANGE:
    case DNTT_TYPE_WITH:
    case DNTT_TYPE_COMMON:
    case DNTT_TYPE_COBSTRUCT:
    case DNTT_TYPE_XREF:
    case DNTT_TYPE_MACRO:
    case DNTT_TYPE_CLASS_SCOPE:
    case DNTT_TYPE_REFERENCE:
    case DNTT_TYPE_PTRMEM:
    case DNTT_TYPE_PTRMEMFUNC:
    case DNTT_TYPE_CLASS:
    case DNTT_TYPE_GENFIELD:
    case DNTT_TYPE_VFUNC:
    case DNTT_TYPE_MEMACCESS:
    case DNTT_TYPE_INHERITANCE:
    case DNTT_TYPE_FRIEND_CLASS:
    case DNTT_TYPE_FRIEND_FUNC:
    case DNTT_TYPE_MODIFIER:
    case DNTT_TYPE_OBJECT_ID:
    case DNTT_TYPE_TEMPLATE:
    case DNTT_TYPE_TEMPLATE_ARG:
    case DNTT_TYPE_FUNC_TEMPLATE:
    case DNTT_TYPE_LINK:
      /* DNTT_TYPE_DYN_ARRAY_DESC ? */
      /* DNTT_TYPE_DESC_SUBRANGE ? */
      /* DNTT_TYPE_BEGIN_EXT ? */
      /* DNTT_TYPE_INLN ? */
      /* DNTT_TYPE_INLN_LIST ? */
      /* DNTT_TYPE_ALIAS ? */
    default:
      return 0;
    }
}