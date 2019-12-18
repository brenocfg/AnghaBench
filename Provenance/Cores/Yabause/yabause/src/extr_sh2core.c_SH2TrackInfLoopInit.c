#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tilInfo_struct ;
struct TYPE_4__ {int maxNum; int /*<<< orphan*/ * match; } ;
struct TYPE_5__ {TYPE_1__ trackInfLoop; } ;
typedef  TYPE_2__ SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 

int SH2TrackInfLoopInit(SH2_struct *context)
{
   context->trackInfLoop.maxNum = 100;
   if ((context->trackInfLoop.match = calloc(context->trackInfLoop.maxNum, sizeof(tilInfo_struct))) == NULL)
      return -1;

   return 0;
}