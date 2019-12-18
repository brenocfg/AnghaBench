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

/* Variables and functions */
 int MMAL_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 char* mmal_status_to_string (int) ; 
 int mmal_vc_init () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_connect(void)
{
   /* this command needs a vchiq connection */
   MMAL_STATUS_T st;
   if ((st = mmal_vc_init()) != MMAL_SUCCESS)
   {
      fprintf(stderr, "failed to initialize mmal vc library (%i:%s)\n",
            st, mmal_status_to_string(st));
      exit(1);
   }
}