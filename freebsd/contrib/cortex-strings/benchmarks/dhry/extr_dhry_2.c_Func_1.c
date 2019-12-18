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
typedef  int /*<<< orphan*/  Enumeration ;
typedef  scalar_t__ Capital_Letter ;

/* Variables and functions */
 scalar_t__ Ch_1_Glob ; 
 int /*<<< orphan*/  Ident_1 ; 
 int /*<<< orphan*/  Ident_2 ; 

Enumeration Func_1 (Capital_Letter Ch_1_Par_Val,
                                           Capital_Letter Ch_2_Par_Val)
 /*************************************************/
     /* executed three times                                         */
     /* first call:      Ch_1_Par_Val == 'H', Ch_2_Par_Val == 'R'    */
     /* second call:     Ch_1_Par_Val == 'A', Ch_2_Par_Val == 'C'    */
     /* third call:      Ch_1_Par_Val == 'B', Ch_2_Par_Val == 'C'    */
 
 {
   Capital_Letter        Ch_1_Loc;
   Capital_Letter        Ch_2_Loc;
 
   Ch_1_Loc = Ch_1_Par_Val;
   Ch_2_Loc = Ch_1_Loc;
   if (Ch_2_Loc != Ch_2_Par_Val)
     /* then, executed */
     return (Ident_1);
   else  /* not executed */
   {
     Ch_1_Glob = Ch_1_Loc;
     return (Ident_2);
    }
 }