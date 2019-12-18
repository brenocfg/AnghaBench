#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t NumFolders; int /*<<< orphan*/ * Files; int /*<<< orphan*/ * Folders; int /*<<< orphan*/ * PackCRCs; int /*<<< orphan*/ * PackCRCsDefined; int /*<<< orphan*/ * PackSizes; } ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CSzAr ;

/* Variables and functions */
 int /*<<< orphan*/  IAlloc_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzAr_Init (TYPE_1__*) ; 
 int /*<<< orphan*/  SzFolder_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SzAr_Free(CSzAr *p, ISzAlloc *alloc)
{
   uint32_t i;
   if (p->Folders)
      for (i = 0; i < p->NumFolders; i++)
         SzFolder_Free(&p->Folders[i], alloc);

   IAlloc_Free(alloc, p->PackSizes);
   IAlloc_Free(alloc, p->PackCRCsDefined);
   IAlloc_Free(alloc, p->PackCRCs);
   IAlloc_Free(alloc, p->Folders);
   IAlloc_Free(alloc, p->Files);
   SzAr_Init(p);
}