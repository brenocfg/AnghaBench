#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; int (* pfn ) (int,char const**) ;scalar_t__ name; } ;

/* Variables and functions */
 int CONNECT ; 
 TYPE_1__* cmds ; 
 int /*<<< orphan*/  do_connect () ; 
 int /*<<< orphan*/  do_usage (int,char const**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mmal_vc_deinit () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (scalar_t__,char const*) ; 
 int stub1 (int,char const**) ; 

int main(int argc, const char **argv)
{
   int i;

   if (argc < 2)
   {
      do_usage(argc, argv);
      exit(1);
   }

   for (i = 0; cmds[i].name; i++)
   {
      if (strcasecmp(cmds[i].name, argv[1]) == 0)
      {
         int rc;
         if (cmds[i].flags & CONNECT)
         {
            do_connect();
         }
         rc = cmds[i].pfn(argc, argv);

         if (cmds[i].flags & CONNECT)
            mmal_vc_deinit();
         return rc;
      }
   }
   fprintf(stderr,"unknown command %s\n", argv[1]);
   return -1;
}