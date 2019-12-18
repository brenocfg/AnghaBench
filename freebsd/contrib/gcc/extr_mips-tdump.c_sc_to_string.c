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
typedef  int sc_t ;

/* Variables and functions */
#define  sc_Abs 151 
#define  sc_Bits 150 
#define  sc_Bss 149 
#define  sc_CdbLocal 148 
#define  sc_CdbSystem 147 
#define  sc_Common 146 
#define  sc_Data 145 
#define  sc_Info 144 
#define  sc_Init 143 
#define  sc_Max 142 
#define  sc_Nil 141 
#define  sc_RData 140 
#define  sc_RegImage 139 
#define  sc_Register 138 
#define  sc_SBss 137 
#define  sc_SCommon 136 
#define  sc_SData 135 
#define  sc_SUndefined 134 
#define  sc_Text 133 
#define  sc_Undefined 132 
#define  sc_UserStruct 131 
#define  sc_Var 130 
#define  sc_VarRegister 129 
#define  sc_Variant 128 

__attribute__((used)) static const char *
sc_to_string (sc_t storage_class)
{
  switch(storage_class)
    {
    case sc_Nil:	 return "Nil";
    case sc_Text:	 return "Text";
    case sc_Data:	 return "Data";
    case sc_Bss:	 return "Bss";
    case sc_Register:	 return "Register";
    case sc_Abs:	 return "Abs";
    case sc_Undefined:	 return "Undefined";
    case sc_CdbLocal:	 return "CdbLocal";
    case sc_Bits:	 return "Bits";
    case sc_CdbSystem:	 return "CdbSystem";
    case sc_RegImage:	 return "RegImage";
    case sc_Info:	 return "Info";
    case sc_UserStruct:	 return "UserStruct";
    case sc_SData:	 return "SData";
    case sc_SBss:	 return "SBss";
    case sc_RData:	 return "RData";
    case sc_Var:	 return "Var";
    case sc_Common:	 return "Common";
    case sc_SCommon:	 return "SCommon";
    case sc_VarRegister: return "VarRegister";
    case sc_Variant:	 return "Variant";
    case sc_SUndefined:	 return "SUndefined";
    case sc_Init:	 return "Init";
    case sc_Max:	 return "Max";
    }

  return "???";
}