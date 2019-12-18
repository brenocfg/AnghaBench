#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ byte ;
struct TYPE_8__ {int /*<<< orphan*/  ReadyInt; int /*<<< orphan*/  ReqInput; int /*<<< orphan*/  ReqOutput; } ;
struct TYPE_7__ {int /*<<< orphan*/  ReadyInt; int /*<<< orphan*/  (* ram_inc ) (TYPE_1__*,int /*<<< orphan*/ *) ;scalar_t__ (* ram_in ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ ADAPTER ;

/* Variables and functions */
 TYPE_6__* PR_RAM ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static byte pr_ready(ADAPTER * a)
{
  byte ReadyCount;
  ReadyCount = (byte)(a->ram_in(a, &PR_RAM->ReqOutput) -
                      a->ram_in(a, &PR_RAM->ReqInput));
  if(!ReadyCount) {
    if(!a->ReadyInt) {
      a->ram_inc(a, &PR_RAM->ReadyInt);
      a->ReadyInt++;
    }
  }
  return ReadyCount;
}