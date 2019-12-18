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
struct TYPE_3__ {int /*<<< orphan*/  (* isInserted ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GUI_MsgBoxClose () ; 
 int /*<<< orphan*/  GUI_MsgBoxOpen (char*,char*,int) ; 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 int /*<<< orphan*/  ISO9660_Mount (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ISO9660_Unmount (char*) ; 
 TYPE_1__* dvd ; 
 int dvd_mounted ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int MountDVD(void)
{
  GUI_MsgBoxOpen("Information", "Mounting DVD ...",1);

  /* check if DVD is already mounted */
  if (dvd_mounted)
  {
		/* unmount DVD */
    ISO9660_Unmount("dvd:");
    dvd_mounted = 0;
  }

  /* check if disc is found */
  if(!dvd->isInserted())
  {
    GUI_WaitPrompt("Error","No Disc inserted !");
    return 0;
  }
		
  /* mount DVD */
  if(!ISO9660_Mount("dvd",dvd))
  {
    GUI_WaitPrompt("Error","Disc can not be read !");
    return 0;
  }

  /* DVD is mounted */
  dvd_mounted = 1;

  GUI_MsgBoxClose();
  return 1;
}