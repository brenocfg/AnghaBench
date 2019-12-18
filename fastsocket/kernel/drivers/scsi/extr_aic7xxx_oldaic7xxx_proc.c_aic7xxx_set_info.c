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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  proc_debug (char*,char*) ; 

__attribute__((used)) static int
aic7xxx_set_info(char *buffer, int length, struct Scsi_Host *HBAptr)
{
  proc_debug("aic7xxx_set_info(): %s\n", buffer);
  return (-ENOSYS);  /* Currently this is a no-op */
}