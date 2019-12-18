#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * renderer_data; TYPE_1__* renderer; } ;
typedef  TYPE_2__ font_data_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int* video_driver_get_threaded () ; 

void font_driver_free(void *font_data)
{
   font_data_t *font = (font_data_t*)font_data;

   if (font)
   {
      bool is_threaded        = false;
#ifdef HAVE_THREADS
      bool *is_threaded_tmp   = video_driver_get_threaded();
      is_threaded             = *is_threaded_tmp;
#endif

      if (font->renderer && font->renderer->free)
         font->renderer->free(font->renderer_data, is_threaded);

      font->renderer      = NULL;
      font->renderer_data = NULL;

      free(font);
   }
}