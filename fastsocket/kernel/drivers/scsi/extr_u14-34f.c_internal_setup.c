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

/* Variables and functions */
 int FALSE ; 
 int MAX_INT_PARAM ; 
 void* TRUE ; 
 int ext_tran ; 
 int have_old_firmware ; 
 int* io_port ; 
 int link_statistics ; 
 int linked_comm ; 
 int max_queue_depth ; 
 void* setup_done ; 
 scalar_t__ simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int tag_mode ; 

__attribute__((used)) static void internal_setup(char *str, int *ints) {
   int i, argc = ints[0];
   char *cur = str, *pc;

   if (argc > 0) {

      if (argc > MAX_INT_PARAM) argc = MAX_INT_PARAM;

      for (i = 0; i < argc; i++) io_port[i] = ints[i + 1];

      io_port[i] = 0;
      setup_done = TRUE;
      }

   while (cur && (pc = strchr(cur, ':'))) {
      int val = 0, c = *++pc;

      if (c == 'n' || c == 'N') val = FALSE;
      else if (c == 'y' || c == 'Y') val = TRUE;
      else val = (int) simple_strtoul(pc, NULL, 0);

      if (!strncmp(cur, "lc:", 3)) linked_comm = val;
      else if (!strncmp(cur, "of:", 3)) have_old_firmware = val;
      else if (!strncmp(cur, "tm:", 3)) tag_mode = val;
      else if (!strncmp(cur, "tc:", 3)) tag_mode = val;
      else if (!strncmp(cur, "mq:", 3))  max_queue_depth = val;
      else if (!strncmp(cur, "ls:", 3))  link_statistics = val;
      else if (!strncmp(cur, "et:", 3))  ext_tran = val;

      if ((cur = strchr(cur, ','))) ++cur;
      }

   return;
}