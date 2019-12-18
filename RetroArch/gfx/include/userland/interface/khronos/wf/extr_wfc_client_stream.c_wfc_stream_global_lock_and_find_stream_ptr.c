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
struct TYPE_4__ {scalar_t__ handle; struct TYPE_4__* next; } ;
typedef  TYPE_1__ WFC_STREAM_T ;
typedef  scalar_t__ WFCNativeStreamType ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_LOCK () ; 
 TYPE_1__* wfc_stream_head ; 

__attribute__((used)) static WFC_STREAM_T *wfc_stream_global_lock_and_find_stream_ptr(WFCNativeStreamType stream)
{
   WFC_STREAM_T *stream_ptr;

   GLOBAL_LOCK();

   stream_ptr = wfc_stream_head;
   while (stream_ptr && stream_ptr->handle != stream)
      stream_ptr = stream_ptr->next;

   return stream_ptr;
}