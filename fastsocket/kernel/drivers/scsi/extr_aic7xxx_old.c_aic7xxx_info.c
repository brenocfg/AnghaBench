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
struct aic7xxx_host {size_t board_name_index; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 char* AIC7XXX_C_VERSION ; 
 char* AIC7XXX_H_VERSION ; 
 char** board_names ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static const char *
aic7xxx_info(struct Scsi_Host *dooh)
{
  static char buffer[256];
  char *bp;
  struct aic7xxx_host *p;

  bp = &buffer[0];
  p = (struct aic7xxx_host *)dooh->hostdata;
  memset(bp, 0, sizeof(buffer));
  strcpy(bp, "Adaptec AHA274x/284x/294x (EISA/VLB/PCI-Fast SCSI) ");
  strcat(bp, AIC7XXX_C_VERSION);
  strcat(bp, "/");
  strcat(bp, AIC7XXX_H_VERSION);
  strcat(bp, "\n");
  strcat(bp, "       <");
  strcat(bp, board_names[p->board_name_index]);
  strcat(bp, ">");

  return(bp);
}