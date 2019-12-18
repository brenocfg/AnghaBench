#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Int_Comp; } ;
struct TYPE_6__ {TYPE_1__ var_1; } ;
struct TYPE_7__ {TYPE_2__ variant; int /*<<< orphan*/  Ptr_Comp; } ;
typedef  int /*<<< orphan*/  Rec_Pointer ;

/* Variables and functions */
 int /*<<< orphan*/  Int_Glob ; 
 TYPE_3__* Null ; 
 int /*<<< orphan*/  Proc_7 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* Ptr_Glob ; 

void Proc_3 (Rec_Pointer *Ptr_Ref_Par)
 /******************/
     /* executed once */
     /* Ptr_Ref_Par becomes Ptr_Glob */
 
 {
   if (Ptr_Glob != Null)
     /* then, executed */
     *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
   Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
 }