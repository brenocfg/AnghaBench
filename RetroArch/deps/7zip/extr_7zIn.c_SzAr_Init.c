#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ NumFiles; scalar_t__ NumFolders; scalar_t__ NumPackStreams; scalar_t__ Files; scalar_t__ Folders; scalar_t__ PackCRCs; scalar_t__ PackCRCsDefined; scalar_t__ PackSizes; } ;
typedef  TYPE_1__ CSzAr ;

/* Variables and functions */

void SzAr_Init(CSzAr *p)
{
   p->PackSizes = 0;
   p->PackCRCsDefined = 0;
   p->PackCRCs = 0;
   p->Folders = 0;
   p->Files = 0;
   p->NumPackStreams = 0;
   p->NumFolders = 0;
   p->NumFiles = 0;
}