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
struct video_viewport {int /*<<< orphan*/  full_height; int /*<<< orphan*/  full_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  screen_event_t ;
struct TYPE_6__ {size_t pointer_count; unsigned int* touch_map; TYPE_1__* pointer; } ;
typedef  TYPE_2__ qnx_input_t ;
struct TYPE_7__ {int full_x; int full_y; } ;
typedef  TYPE_3__ gl_t ;
struct TYPE_5__ {int contact_id; size_t map; int /*<<< orphan*/  full_y; int /*<<< orphan*/  full_x; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 unsigned int MAX_TOUCH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,int,int,...) ; 
#define  SCREEN_EVENT_MTOUCH_MOVE 130 
#define  SCREEN_EVENT_MTOUCH_RELEASE 129 
#define  SCREEN_EVENT_MTOUCH_TOUCH 128 
 int /*<<< orphan*/  SCREEN_PROPERTY_SOURCE_POSITION ; 
 int /*<<< orphan*/  SCREEN_PROPERTY_TOUCH_ID ; 
 int /*<<< orphan*/  screen_get_event_property_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ video_driver_get_ptr (int) ; 
 int /*<<< orphan*/  video_driver_translate_coord_viewport_wrap (struct video_viewport*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qnx_process_touch_event(
      qnx_input_t *qnx, screen_event_t event, int type)
{
   int contact_id, pos[2];
   unsigned i, j;

   screen_get_event_property_iv(event,
         SCREEN_PROPERTY_TOUCH_ID, (int*)&contact_id);
   screen_get_event_property_iv(event,
         SCREEN_PROPERTY_SOURCE_POSITION, pos);

   switch(type)
   {
      case SCREEN_EVENT_MTOUCH_TOUCH:
         /* Find a free touch struct. */
         for(i = 0; i < MAX_TOUCH; ++i)
         {
            if(qnx->pointer[i].contact_id == -1)
            {
               struct video_viewport vp;

               vp.x                        = 0;
               vp.y                        = 0;
               vp.width                    = 0;
               vp.height                   = 0;
               vp.full_width               = 0;
               vp.full_height              = 0;

               qnx->pointer[i].contact_id  = contact_id;

               video_driver_translate_coord_viewport_wrap(
                     &vp,
                     pos[0], pos[1],
                     &qnx->pointer[i].x, &qnx->pointer[i].y,
                     &qnx->pointer[i].full_x, &qnx->pointer[i].full_y);

               /* Add this pointer to the map to signal it's valid. */
               qnx->pointer[i].map = qnx->pointer_count;
               qnx->touch_map[qnx->pointer_count] = i;
               qnx->pointer_count++;
               break;
            }
         }
#if 0
         RARCH_LOG("New Touch: x:%d, y:%d, id:%d\n", pos[0], pos[1], contact_id);
         RARCH_LOG("Map: %d %d %d %d %d %d\n", qnx->touch_map[0], qnx->touch_map[1],
               qnx->touch_map[2], qnx->touch_map[3], qnx->touch_map[4],
               qnx->touch_map[5]);
#endif
         break;

      case SCREEN_EVENT_MTOUCH_RELEASE:
         for(i = 0; i < MAX_TOUCH; ++i)
         {
            if(qnx->pointer[i].contact_id == contact_id)
            {
               /* Invalidate the finger. */
               qnx->pointer[i].contact_id = -1;

               /* Remove pointer from map and shift
                * remaining valid ones to the front. */
               qnx->touch_map[qnx->pointer[i].map] = -1;
               for(j = qnx->pointer[i].map; j < qnx->pointer_count; ++j)
               {
                  qnx->touch_map[j] = qnx->touch_map[j+1];
                  qnx->pointer[qnx->touch_map[j+1]].map = j;
                  qnx->touch_map[j+1] = -1;
               }
               qnx->pointer_count--;
               break;
            }
         }
#if 0
         RARCH_LOG("Release: x:%d, y:%d, id:%d\n", pos[0], pos[1], contact_id);
         RARCH_LOG("Map: %d %d %d %d %d %d\n", qnx->touch_map[0], qnx->touch_map[1],
               qnx->touch_map[2], qnx->touch_map[3], qnx->touch_map[4],
               qnx->touch_map[5]);
#endif
         break;

      case SCREEN_EVENT_MTOUCH_MOVE:
         /* Find the finger we're tracking and update. */
         for(i = 0; i < qnx->pointer_count; ++i)
         {
            if(qnx->pointer[i].contact_id == contact_id)
            {
               struct video_viewport vp;

               vp.x                        = 0;
               vp.y                        = 0;
               vp.width                    = 0;
               vp.height                   = 0;
               vp.full_width               = 0;
               vp.full_height              = 0;

#if 0
               gl_t *gl = (gl_t*)video_driver_get_ptr(false);

               /*During a move, we can go ~30 pixel into the
                * bezel which gives negative numbers or
                * numbers larger than the screen resolution.
                *
                * Normalize. */
               if(pos[0] < 0)
                  pos[0] = 0;
               if(pos[0] > gl->full_x)
                  pos[0] = gl->full_x;

               if(pos[1] < 0)
                  pos[1] = 0;
               if(pos[1] > gl->full_y)
                  pos[1] = gl->full_y;
#endif

               video_driver_translate_coord_viewport_wrap(&vp,
                     pos[0], pos[1],
                     &qnx->pointer[i].x, &qnx->pointer[i].y,
                     &qnx->pointer[i].full_x, &qnx->pointer[i].full_y);
#if 0
               RARCH_LOG("Move: x:%d, y:%d, id:%d\n", pos[0], pos[1],
                     contact_id);
#endif
               break;
            }
         }
         break;
   }
}