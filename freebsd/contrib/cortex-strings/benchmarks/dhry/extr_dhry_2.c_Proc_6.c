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
typedef  int Enumeration ;

/* Variables and functions */
 int /*<<< orphan*/  Func_3 (int) ; 
#define  Ident_1 132 
#define  Ident_2 131 
#define  Ident_3 130 
#define  Ident_4 129 
#define  Ident_5 128 
 int Int_Glob ; 

void Proc_6 (Enumeration Enum_Val_Par, Enumeration *Enum_Ref_Par)
 /*********************************/
     /* executed once */
     /* Enum_Val_Par == Ident_3, Enum_Ref_Par becomes Ident_2 */
 
 {
   *Enum_Ref_Par = Enum_Val_Par;
   if (! Func_3 (Enum_Val_Par))
     /* then, not executed */
     *Enum_Ref_Par = Ident_4;
   switch (Enum_Val_Par)
   {
     case Ident_1: 
       *Enum_Ref_Par = Ident_1;
       break;
     case Ident_2: 
       if (Int_Glob > 100)
         /* then */
       *Enum_Ref_Par = Ident_1;
       else *Enum_Ref_Par = Ident_4;
       break;
     case Ident_3: /* executed */
       *Enum_Ref_Par = Ident_2;
       break;
     case Ident_4: break;
     case Ident_5: 
       *Enum_Ref_Par = Ident_3;
       break;
   } /* switch */
 }