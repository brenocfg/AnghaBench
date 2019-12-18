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
typedef  int /*<<< orphan*/  perlinuxjoy_struct ;
struct TYPE_4__ {int gl_pathc; int /*<<< orphan*/ * gl_pathv; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int /*<<< orphan*/  LinuxJoyInit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int joycount ; 
 scalar_t__ joysticks ; 
 scalar_t__ malloc (int) ; 

int PERLinuxJoyInit(void)
{
   int i;
   int fd;
   glob_t globbuf;

   glob("/dev/input/js*", 0, NULL, &globbuf);

   joycount = globbuf.gl_pathc;
   joysticks = malloc(sizeof(perlinuxjoy_struct) * joycount);

   for(i = 0;i < globbuf.gl_pathc;i++)
      LinuxJoyInit(joysticks + i, globbuf.gl_pathv[i]);

   globfree(&globbuf);

   return 0;
}