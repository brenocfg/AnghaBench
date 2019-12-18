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
typedef  scalar_t__ One_Fifty ;

/* Variables and functions */

void Proc_7 (One_Fifty Int_1_Par_Val, One_Fifty Int_2_Par_Val,
                                              One_Fifty *Int_Par_Ref)
 /**********************************************/
     /* executed three times                                      */
     /* first call:      Int_1_Par_Val == 2, Int_2_Par_Val == 3,  */
     /*                  Int_Par_Ref becomes 7                    */
     /* second call:     Int_1_Par_Val == 10, Int_2_Par_Val == 5, */
     /*                  Int_Par_Ref becomes 17                   */
     /* third call:      Int_1_Par_Val == 6, Int_2_Par_Val == 10, */
     /*                  Int_Par_Ref becomes 18                   */

 {
   One_Fifty Int_Loc;
 
   Int_Loc = Int_1_Par_Val + 2;
   *Int_Par_Ref = Int_2_Par_Val + Int_Loc;
 }