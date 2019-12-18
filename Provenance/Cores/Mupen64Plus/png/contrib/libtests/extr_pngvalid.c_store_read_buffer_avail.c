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
struct TYPE_6__ {struct TYPE_6__* prev; } ;
typedef  TYPE_2__ png_store_buffer ;
struct TYPE_7__ {size_t readpos; int /*<<< orphan*/  pread; TYPE_2__* next; TYPE_1__* current; } ;
typedef  TYPE_3__ png_store ;
struct TYPE_5__ {size_t datacount; TYPE_2__ data; } ;

/* Variables and functions */
 scalar_t__ STORE_BUFFER_SIZE ; 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static size_t
store_read_buffer_avail(png_store *ps)
{
   if (ps->current != NULL && ps->next != NULL)
   {
      png_store_buffer *next = &ps->current->data;
      size_t cbAvail = ps->current->datacount;

      while (next != ps->next && next != NULL)
      {
         next = next->prev;
         cbAvail += STORE_BUFFER_SIZE;
      }

      if (next != ps->next)
         png_error(ps->pread, "buffer read error");

      if (cbAvail > ps->readpos)
         return cbAvail - ps->readpos;
   }

   return 0;
}