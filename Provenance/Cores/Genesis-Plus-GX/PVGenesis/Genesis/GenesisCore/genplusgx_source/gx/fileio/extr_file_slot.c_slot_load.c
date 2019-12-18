#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u32 ;
struct TYPE_7__ {unsigned long len; } ;
typedef  TYPE_1__ card_file ;
struct TYPE_9__ {int realchecksum; } ;
struct TYPE_8__ {unsigned long* sram; int /*<<< orphan*/  crc; int /*<<< orphan*/  on; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_Close (TYPE_1__*) ; 
 int CARD_GetSectorSize (int,unsigned long*) ; 
 int /*<<< orphan*/  CARD_Init (char*,char*) ; 
 int CARD_Open (int,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  CARD_Read (TYPE_1__*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  CARD_Unmount (int) ; 
 int /*<<< orphan*/  CARD_WORKAREA ; 
 unsigned long CHUNKSIZE ; 
 int /*<<< orphan*/  CardMount (int) ; 
 char* DEFAULT_PATH ; 
 int /*<<< orphan*/  GUI_MsgBoxClose () ; 
 int /*<<< orphan*/  GUI_MsgBoxOpen (char*,char*,int) ; 
 int /*<<< orphan*/  GUI_WaitPrompt (char*,char*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SysArea ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ memalign (int,unsigned long) ; 
 int /*<<< orphan*/  memcpy (unsigned long*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* rom_filename ; 
 TYPE_3__ rominfo ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 TYPE_2__ sram ; 
 scalar_t__ state_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uncompress (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *,unsigned long) ; 

int slot_load(int slot, int device)
{
  char filename[MAXPATHLEN];
  unsigned long filesize, done = 0;
  u8 *buffer;

  /* File Type */
  if (slot > 0)
  {
    GUI_MsgBoxOpen("Information","Loading State ...",1);
  }
  else
  {
    if (!sram.on)
    {
      GUI_WaitPrompt("Error","Backup RAM is disabled !");
      return 0;
    }

    GUI_MsgBoxOpen("Information","Loading Backup RAM ...",1);
  }

  /* Device Type */
  if (!device)
  {
    /* FAT file */
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
    if (!fp)
    {
      GUI_WaitPrompt("Error","Unable to open file !");
      return 0;
    }

    /* Get file size */
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* allocate buffer */
    buffer = (u8 *)memalign(32,filesize);
    if (!buffer)
    {
      GUI_WaitPrompt("Error","Unable to allocate memory !");
      fclose(fp);
      return 0;
    }

    /* Read into buffer (2k blocks) */
    while (filesize > CHUNKSIZE)
    {
      fread(buffer + done, CHUNKSIZE, 1, fp);
      done += CHUNKSIZE;
      filesize -= CHUNKSIZE;
    }

    /* Read remaining bytes */
    fread(buffer + done, filesize, 1, fp);
    done += filesize;

    /* Close file */
    fclose(fp);
  }
  else
  {
    /* Memory Card file */
    if (slot > 0)
    {
      sprintf(filename, "MD-%04X.gp%d", rominfo.realchecksum, slot - 1);
    }
    else
    {
      sprintf(filename, "MD-%04X.srm", rominfo.realchecksum);
    }

    /* Initialise the CARD system */
    char action[64];
    memset(&SysArea, 0, CARD_WORKAREA);
    CARD_Init("GENP", "00");

    /* CARD slot */
    device--;

    /* Attempt to mount the card */
    if (!CardMount(device))
    {
      GUI_WaitPrompt("Error","Unable to mount memory card");
      return 0;
    }
    
    /* Retrieve the sector size */
    u32 SectorSize = 0;
    int CardError = CARD_GetSectorSize(device, &SectorSize);
    if (!SectorSize)
    {
      sprintf(action, "Invalid sector size (%d)", CardError);
      GUI_WaitPrompt("Error",action);
      CARD_Unmount(device);
      return 0;
    }

    /* Open file */
    card_file CardFile;
    CardError = CARD_Open(device, filename, &CardFile);
    if (CardError)
    {
      sprintf(action, "Unable to open file (%d)", CardError);
      GUI_WaitPrompt("Error",action);
      CARD_Unmount(device);
      return 0;
    }

    /* Get file size */
    filesize = CardFile.len;
    if (filesize % SectorSize)
    {
      filesize = ((filesize / SectorSize) + 1) * SectorSize;
    }

    /* Allocate buffer */
    u8 *in = (u8 *)memalign(32, filesize);
    if (!in)
    {
      GUI_WaitPrompt("Error","Unable to allocate memory !");
      CARD_Close(&CardFile);
      CARD_Unmount(device);
      return 0;
    }

    /* Read file sectors */
    while (filesize > 0)
    {
      CARD_Read(&CardFile, &in[done], SectorSize, done);
      done += SectorSize;
      filesize -= SectorSize;
    }

    /* Close file */
    CARD_Close(&CardFile);
    CARD_Unmount(device);

    /* Uncompressed file size */
    memcpy(&filesize, in + 2112, 4);
    buffer = (u8 *)memalign(32, filesize);
    if (!buffer)
    {
      free(in);
      GUI_WaitPrompt("Error","Unable to allocate memory !");
      return 0;
    }

    /* Uncompress file */
    uncompress ((Bytef *)buffer, &filesize, (Bytef *)(in + 2112 + 4), done - 2112 - 4);
    free(in);
  }

  if (slot > 0)
  {
    /* Load state */
    if (state_load(buffer) <= 0)
    {
      free(buffer);
      GUI_WaitPrompt("Error","Invalid state file !");
      return 0;
    }
  }
  else
  {
    /* load SRAM */
    memcpy(sram.sram, buffer, 0x10000);

    /* update CRC */
    sram.crc = crc32(0, sram.sram, 0x10000);
  }

  free(buffer);
  GUI_MsgBoxClose();
  return 1;
}