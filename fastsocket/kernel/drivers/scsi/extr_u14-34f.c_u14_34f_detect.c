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
struct scsi_host_template {char* proc_name; } ;

/* Variables and functions */
 int MAX_BOARDS ; 
 size_t MAX_INT_PARAM ; 
 scalar_t__ SKIP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  boot_options ; 
 scalar_t__* io_port ; 
 unsigned int num_boards ; 
 int /*<<< orphan*/  option_setup (int /*<<< orphan*/ ) ; 
 scalar_t__ port_detect (scalar_t__,unsigned int,struct scsi_host_template*) ; 
 int /*<<< orphan*/  setup_done ; 
 int /*<<< orphan*/ ** sh ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u14_34f_detect(struct scsi_host_template *tpnt) {
   unsigned int j = 0, k;

   tpnt->proc_name = "u14-34f";

   if(strlen(boot_options)) option_setup(boot_options);

#if defined(MODULE)
   /* io_port could have been modified when loading as a module */
   if(io_port[0] != SKIP) {
      setup_done = TRUE;
      io_port[MAX_INT_PARAM] = 0;
      }
#endif

   for (k = 0; k < MAX_BOARDS + 1; k++) sh[k] = NULL;

   for (k = 0; io_port[k]; k++) {

      if (io_port[k] == SKIP) continue;

      if (j < MAX_BOARDS && port_detect(io_port[k], j, tpnt)) j++;
      }

   num_boards = j;
   return j;
}