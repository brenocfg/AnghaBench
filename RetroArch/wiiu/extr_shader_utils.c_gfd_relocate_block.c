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
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ dataSize; } ;
struct TYPE_7__ {scalar_t__ data; TYPE_1__ header; } ;
struct TYPE_6__ {scalar_t__ magic; int patchOffset; int patchCount; } ;
typedef  TYPE_2__ GFDRelocationHeader ;
typedef  TYPE_3__ GFDBlock ;

/* Variables and functions */
 scalar_t__ GFD_BLOCK_RELOCATIONS_MAGIC ; 
 int GFD_RELOCATIONS_DATA ; 
 int GFD_RELOCATIONS_TEXT ; 
 int GFD_RELOCATIONS_TYPE_MASK ; 
 int GFD_RELOCATIONS_VALUE_MASK ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static bool gfd_relocate_block(GFDBlock* block)
{

   GFDRelocationHeader* rel = (GFDRelocationHeader*)(block->data + block->header.dataSize) - 1;

   if (rel->magic != GFD_BLOCK_RELOCATIONS_MAGIC)
   {
      printf("wrong relocations magic number.\n");
      return false;
   }

   if((rel->patchOffset & GFD_RELOCATIONS_TYPE_MASK) != GFD_RELOCATIONS_DATA)
   {
      printf("wrong data relocations mask.\n");
      return false;
   }

   u32* patches = (u32*)(block->data + (rel->patchOffset & GFD_RELOCATIONS_VALUE_MASK));

   for(int i=0; i < rel->patchCount; i++)
   {
      if(patches[i])
      {
         if((patches[i] & GFD_RELOCATIONS_TYPE_MASK) != GFD_RELOCATIONS_DATA)
         {
            printf("wrong patch relocations mask.\n");
            return false;
         }

         u32* ptr = (u32*)(block->data + (patches[i] & GFD_RELOCATIONS_VALUE_MASK));
         if((((*ptr) & GFD_RELOCATIONS_TYPE_MASK) != GFD_RELOCATIONS_DATA) &&
            (((*ptr) & GFD_RELOCATIONS_TYPE_MASK) != GFD_RELOCATIONS_TEXT))
         {
            printf("wrong relocations mask.\n");
            return false;
         }
         *ptr = (u32)block->data + ((*ptr) & GFD_RELOCATIONS_VALUE_MASK);
      }
   }

   return true;
}