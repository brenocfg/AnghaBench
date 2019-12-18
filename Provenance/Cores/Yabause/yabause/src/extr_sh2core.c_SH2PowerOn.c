#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetGPR ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetPC ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ (* GetVBR ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/  MappedMemoryReadLong (scalar_t__) ; 
 TYPE_1__* SH2Core ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void SH2PowerOn(SH2_struct *context) {
   u32 VBR = SH2Core->GetVBR(context);
   SH2Core->SetPC(context, MappedMemoryReadLong(VBR));
   SH2Core->SetGPR(context, 15, MappedMemoryReadLong(VBR+4));
}