#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct js_event {int type; size_t number; int value; } ;
struct TYPE_3__ {int fd; int axiscount; int* axis; } ;
typedef  TYPE_1__ perlinuxjoy_struct ;

/* Variables and functions */
 int JS_EVENT_AXIS ; 
 int JS_EVENT_INIT ; 
 int MAXAXIS ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int* malloc (int) ; 
 int open (char const*,int) ; 
 size_t read (int,struct js_event*,int) ; 

__attribute__((used)) static void LinuxJoyInit(perlinuxjoy_struct * joystick, const char * path)
{
   int i;
   int fd;
   int axisinit[MAXAXIS];
   struct js_event evt;
   size_t num_read;

   joystick->fd = open(path, O_RDONLY | O_NONBLOCK);

   if (joystick->fd == -1) return;

   joystick->axiscount = 0;

   while ((num_read = read(joystick->fd, &evt, sizeof(struct js_event))) > 0)
   {
      if (evt.type == (JS_EVENT_AXIS | JS_EVENT_INIT))
      {
         axisinit[evt.number] = evt.value;
         if (evt.number + 1 > joystick->axiscount)
         {
            joystick->axiscount = evt.number + 1;
         }
      }
   }

   if (joystick->axiscount > MAXAXIS) joystick->axiscount = MAXAXIS;

   joystick->axis = malloc(sizeof(int) * joystick->axiscount);
   for(i = 0;i < joystick->axiscount;i++)
   {
      joystick->axis[i] = axisinit[i];
   }
}