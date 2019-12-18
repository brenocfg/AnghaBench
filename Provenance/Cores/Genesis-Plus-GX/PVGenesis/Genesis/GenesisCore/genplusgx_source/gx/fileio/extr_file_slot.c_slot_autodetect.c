#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_11__ {int valid; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; int /*<<< orphan*/  month; scalar_t__ year; } ;
typedef  TYPE_1__ t_slot ;
struct tm {int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; scalar_t__ tm_year; } ;
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct TYPE_12__ {int /*<<< orphan*/  time; } ;
typedef  TYPE_2__ card_stat ;
struct TYPE_13__ {int /*<<< orphan*/  filenum; } ;
typedef  TYPE_3__ card_file ;
struct TYPE_14__ {int realchecksum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_Close (TYPE_3__*) ; 
 scalar_t__ CARD_ERROR_READY ; 
 int /*<<< orphan*/  CARD_GetStatus (int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CARD_Init (char*,char*) ; 
 scalar_t__ CARD_Open (int,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  CARD_Unmount (int) ; 
 int CARD_WORKAREA ; 
 scalar_t__ CardMount (int) ; 
 char* DEFAULT_PATH ; 
 int MAXPATHLEN ; 
 TYPE_1__ SysArea ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* rom_filename ; 
 TYPE_5__ rominfo ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

void slot_autodetect(int slot, int device, t_slot *ptr)
{
  if (!ptr) return;
  
  char filename[MAXPATHLEN];
  memset(ptr,0,sizeof(t_slot));

  if (!device)
  {
    /* FAT support */
    if (slot > 0)
    {
      sprintf (filename,"%s/saves/%s.gp%d", DEFAULT_PATH, rom_filename, slot - 1);
    }
    else
    {
      sprintf (filename,"%s/saves/%s.srm", DEFAULT_PATH, rom_filename);
    }

    /* Open file */
    FILE *fp = fopen(filename, "rb");
    if (fp)
    {
      /* Retrieve date & close */
	    struct stat filestat;
			stat(filename, &filestat);
      struct tm *timeinfo = localtime(&filestat.st_mtime);
      ptr->year = 1900 + timeinfo->tm_year;
      ptr->month = timeinfo->tm_mon;
      ptr->day = timeinfo->tm_mday;
      ptr->hour = timeinfo->tm_hour;
      ptr->min = timeinfo->tm_min;
      fclose(fp);
      ptr->valid = 1;
    }
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
      /* Open file */
      card_file CardFile;
      if (CARD_Open(device, filename, &CardFile) == CARD_ERROR_READY)
      {
        /* Retrieve date & close */
        card_stat CardStatus;
        CARD_GetStatus(device, CardFile.filenum, &CardStatus);
        time_t rawtime = CardStatus.time;
	      struct tm *timeinfo = localtime(&rawtime);
        ptr->year = 1900 + timeinfo->tm_year;
        ptr->month = timeinfo->tm_mon;
        ptr->day = timeinfo->tm_mday;
        ptr->hour = timeinfo->tm_hour;
        ptr->min = timeinfo->tm_min;
        CARD_Close(&CardFile);
        ptr->valid = 1;
      }
      CARD_Unmount(device);
    }
  }
}