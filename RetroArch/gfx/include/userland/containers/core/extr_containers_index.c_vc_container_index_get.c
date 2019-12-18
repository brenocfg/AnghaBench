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
struct TYPE_6__ {int next; scalar_t__ max_time; TYPE_1__* entry; } ;
typedef  TYPE_2__ VC_CONTAINER_INDEX_T ;
struct TYPE_5__ {scalar_t__ time; scalar_t__ file_offset; } ;

/* Variables and functions */
 size_t ENTRY (TYPE_2__*,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

VC_CONTAINER_STATUS_T vc_container_index_get( VC_CONTAINER_INDEX_T *index, int later, int64_t *time, int64_t *file_offset, int *past )
{
   int guess, start, end, entry;

   if(index == NULL || index->next == 0)
      return VC_CONTAINER_ERROR_FAILED;

   guess = start = 0;
   end = index->next-1;

   *past = *time > index->max_time;

   while(end-start > 1)
   {
      int64_t gtime;
      guess = (start+end)>>1;
      gtime = index->entry[ENTRY(index, guess)].time;

      if(*time < gtime)
         end = guess;
      else if(*time > gtime)
         start = guess;
      else
         break;
   }

   if (*time != index->entry[ENTRY(index, guess)].time)
   {
      if(later)
      {
         if(*time <= index->entry[ENTRY(index, start)].time)
            guess = start;
         else
            guess = end;
      }
      else
      {
         if(*time >= index->entry[ENTRY(index, end)].time)
            guess = end;
         else
            guess = start;
      }
   }

   entry = ENTRY(index, guess);
   *time = index->entry[entry].time;
   *file_offset = index->entry[entry].file_offset;

   return VC_CONTAINER_SUCCESS;
}