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
typedef  int MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int mmal_component_create (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int do_create(int argc, const char **argv)
{
   MMAL_COMPONENT_T *comp;
   MMAL_STATUS_T st;
   if (argc != 3)
   {
      printf("usage: mmal-vc-diag create <name>\n");
      printf("   e.g. vc.camera\n");
      exit(1);
   }
   st = mmal_component_create(argv[2], &comp);
   if (comp)
      printf("Created component\n");
   else
      printf("Failed to create %s: %d\n", argv[2], st);

   return 0;
}