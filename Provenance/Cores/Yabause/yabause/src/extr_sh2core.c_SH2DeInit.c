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
struct TYPE_2__ {int /*<<< orphan*/  (* DeInit ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * MSH2 ; 
 TYPE_1__* SH2Core ; 
 int /*<<< orphan*/  SH2TrackInfLoopDeInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSH2 ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

void SH2DeInit()
{
   if (SH2Core)
      SH2Core->DeInit();
   SH2Core = NULL;

   if (MSH2)
   {
      SH2TrackInfLoopDeInit(MSH2);
      free(MSH2);
   }
   MSH2 = NULL;

   if (SSH2)
   {
      SH2TrackInfLoopDeInit(SSH2);
      free(SSH2);
   }
   SSH2 = NULL;
}