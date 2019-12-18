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
typedef  int st_t ;

/* Variables and functions */
#define  st_Block 152 
#define  st_Constant 151 
#define  st_End 150 
#define  st_Enum 149 
#define  st_Expr 148 
#define  st_File 147 
#define  st_Forward 146 
#define  st_Global 145 
#define  st_Label 144 
#define  st_Local 143 
#define  st_Max 142 
#define  st_Member 141 
#define  st_Nil 140 
#define  st_Number 139 
#define  st_Param 138 
#define  st_Proc 137 
#define  st_RegReloc 136 
#define  st_StaParam 135 
#define  st_Static 134 
#define  st_StaticProc 133 
#define  st_Str 132 
#define  st_Struct 131 
#define  st_Type 130 
#define  st_Typedef 129 
#define  st_Union 128 

__attribute__((used)) static const char *
st_to_string (st_t symbol_type)
{
  switch(symbol_type)
    {
    case st_Nil:	return "Nil";
    case st_Global:	return "Global";
    case st_Static:	return "Static";
    case st_Param:	return "Param";
    case st_Local:	return "Local";
    case st_Label:	return "Label";
    case st_Proc:	return "Proc";
    case st_Block:	return "Block";
    case st_End:	return "End";
    case st_Member:	return "Member";
    case st_Typedef:	return "Typedef";
    case st_File:	return "File";
    case st_RegReloc:	return "RegReloc";
    case st_Forward:	return "Forward";
    case st_StaticProc:	return "StaticProc";
    case st_Constant:	return "Constant";
    case st_StaParam:	return "StaticParam";
#ifdef stStruct
    case st_Struct:	return "Struct";
    case st_Union:	return "Union";
    case st_Enum:	return "Enum";
#endif
    case st_Str:	return "String";
    case st_Number:	return "Number";
    case st_Expr:	return "Expr";
    case st_Type:	return "Type";
    case st_Max:	return "Max";
    }

  return "???";
}