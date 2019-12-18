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
typedef  scalar_t__ Enumeration ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ Ident_3 ; 

Boolean Func_3 (Enumeration Enum_Par_Val)
 /***************************/
     /* executed once        */
     /* Enum_Par_Val == Ident_3 */
     
 {
   Enumeration Enum_Loc;
 
   Enum_Loc = Enum_Par_Val;
   if (Enum_Loc == Ident_3)
     /* then, executed */
     return (true);
   else /* not executed */
     return (false);
 }