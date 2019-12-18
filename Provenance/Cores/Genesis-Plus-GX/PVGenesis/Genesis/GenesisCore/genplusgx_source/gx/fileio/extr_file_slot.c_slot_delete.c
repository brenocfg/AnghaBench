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
struct TYPE_2__ {int realchecksum; } ;

/* Variables and functions */
 int CARD_Delete (int,char*) ; 
 int /*<<< orphan*/  CARD_Init (char*,char*) ; 
 int /*<<< orphan*/  CARD_Unmount (int) ; 
 int /*<<< orphan*/  CARD_WORKAREA ; 
 scalar_t__ CardMount (int) ; 
 char* DEFAULT_PATH ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SysArea ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int remove (char*) ; 
 char* rom_filename ; 
 TYPE_1__ rominfo ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int slot_delete(int slot, int device)
{
  char filename[MAXPATHLEN];
  int ret = 0;

  if (!device)
  {
    /* FAT support */
    if (slot > 0)
    {
      /* remove screenshot */
      sprintf(filename,"%s/saves/%s__%d.png", DEFAULT_PATH, rom_filename, slot - 1);
      remove(filename);

      sprintf (filename,"%s/saves/%s.gp%d", DEFAULT_PATH, rom_filename, slot - 1);
    }
    else
    {
      sprintf (filename,"%s/saves/%s.srm", DEFAULT_PATH, rom_filename);
    }

    /* Delete file */
    ret = remove(filename);
  }
  else
  {
    /* Memory Card support */
    if (slot > 0)
      sprintf(filename,"MD-%04X.gp%d", rominfo.realchecksum, slot - 1);
    else
      sprintf(filename,"MD-%04X.srm", rominfo.realchecksum);

    /* Initialise the CARD system */
    memset(&SysArea, 0, CARD_WORKAREA);
    CARD_Init("GENP", "00");

    /* CARD slot */
    device--;

    /* Mount CARD */
    if (CardMount(device))
    {
      /* Delete file */
      ret = CARD_Delete(device,filename);
      CARD_Unmount(device);
    }
  }

  return ret;
}