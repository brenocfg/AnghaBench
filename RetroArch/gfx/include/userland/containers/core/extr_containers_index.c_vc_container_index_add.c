#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_6__ {int next; scalar_t__ max_time; int count; int max_count; int len; int gap; int mgap; TYPE_1__* entry; } ;
typedef  TYPE_2__ VC_CONTAINER_INDEX_T ;
struct TYPE_5__ {scalar_t__ time; scalar_t__ file_offset; } ;

/* Variables and functions */
 int ENTRY (TYPE_2__*,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

VC_CONTAINER_STATUS_T vc_container_index_add( VC_CONTAINER_INDEX_T *index, int64_t time, int64_t file_offset )
{
   if(index == NULL)
      return VC_CONTAINER_ERROR_FAILED;

   // reject entries if they are in part of the time covered
   if(index->next != 0 && time <= index->max_time)
      return VC_CONTAINER_SUCCESS;

   index->count++;
   if(index->count == (1<<index->max_count))
   {
      int entry;
      if(index->next == (1<<index->len))
      {
         // New entry doesn't fit, we discard every other index record
         // by changing how we map index positions to array entry indexes.
         index->next >>= 1;
         index->gap++;
         index->mgap--;
         index->max_count++;

         if(index->gap == index->len)
         {
            index->gap = 0;
            index->mgap = index->len;
         }
      }

      entry = ENTRY(index, index->next);

      index->entry[entry].file_offset = file_offset;
      index->entry[entry].time = time;
      index->count = 0;
      index->next++;
      index->max_time = time;
   }

   return VC_CONTAINER_SUCCESS;
}