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
struct TYPE_2__ {int /*<<< orphan*/  matchFinderMt; scalar_t__ mtMode; } ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinderMt_ReleaseStream (int /*<<< orphan*/ *) ; 

void LzmaEnc_Finish(CLzmaEncHandle pp)
{
#ifndef _7ZIP_ST
   CLzmaEnc *p = (CLzmaEnc *)pp;
   if (p->mtMode)
      MatchFinderMt_ReleaseStream(&p->matchFinderMt);
#endif
}