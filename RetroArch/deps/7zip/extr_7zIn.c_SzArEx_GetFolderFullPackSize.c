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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
struct TYPE_5__ {scalar_t__* PackSizes; TYPE_2__* Folders; } ;
struct TYPE_7__ {size_t* FolderStartPackStreamIndex; TYPE_1__ db; } ;
struct TYPE_6__ {size_t NumPackStreams; } ;
typedef  TYPE_2__ CSzFolder ;
typedef  TYPE_3__ CSzArEx ;

/* Variables and functions */
 int SZ_ERROR_FAIL ; 
 int SZ_OK ; 

int SzArEx_GetFolderFullPackSize(const CSzArEx *p, uint32_t folderIndex, uint64_t *resSize)
{
   uint32_t packStreamIndex = p->FolderStartPackStreamIndex[folderIndex];
   CSzFolder *folder = p->db.Folders + folderIndex;
   uint64_t size = 0;
   uint32_t i;
   for (i = 0; i < folder->NumPackStreams; i++)
   {
      uint64_t t = size + p->db.PackSizes[packStreamIndex + i];
      if (t < size) /* check it */
         return SZ_ERROR_FAIL;
      size = t;
   }
   *resSize = size;
   return SZ_OK;
}