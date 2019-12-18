#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  EmscriptenFullscreenChangeEvent ;
typedef  int /*<<< orphan*/  EM_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EM_TRUE ; 
 int emscripten_fullscreen_reinit ; 

__attribute__((used)) static EM_BOOL emscripten_fullscreenchange_cb(int event_type,
   const EmscriptenFullscreenChangeEvent *fullscreen_change_event,
   void *user_data)
{
   (void)event_type;
   (void)fullscreen_change_event;
   (void)user_data;

   emscripten_fullscreen_reinit = 5;

   return EM_TRUE;
}