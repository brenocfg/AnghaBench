#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int last; int end; TYPE_1__* tracks; } ;
struct TYPE_6__ {int sectorSize; int loaded; int /*<<< orphan*/  status; TYPE_2__ toc; } ;
struct TYPE_4__ {int start; int end; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int CT_BIN ; 
 int EL_ANOMALY ; 
 int EL_STATUS ; 
 int /*<<< orphan*/  NO_DISC ; 
 TYPE_3__ cdd ; 
 int /*<<< orphan*/  cdd_unload () ; 
 int /*<<< orphan*/  elprintf (int,char*) ; 
 int load_cd_image (char const*,int*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  pm_read (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int* toc_dungeon ; 
 int* toc_ffight ; 
 int* toc_ffightj ; 
 int* toc_lunar ; 
 int* toc_shadow ; 
 int* toc_snatcher ; 

int cdd_load(const char *filename, int type)
{
  char header[0x210];
  int ret;

  /* first unmount any loaded disc */
  cdd_unload();

  /* genplus parses cue here, in PD we use our own parser */
  ret = load_cd_image(filename, &type);
  if (ret != 0)
    return ret;

  /* read first 16 bytes */
  pm_read(header, 0x10, cdd.toc.tracks[0].fd);

  /* look for valid CD image ID string */
  if (memcmp("SEGADISCSYSTEM", header, 14))
  {    
    /* if not found, read next 16 bytes */
    pm_read(header, 0x10, cdd.toc.tracks[0].fd);

    /* look again for valid CD image ID string */
    if (memcmp("SEGADISCSYSTEM", header, 14))
    {
      elprintf(EL_STATUS|EL_ANOMALY, "cd: bad cd image?");
      /* assume bin without security code */
    }

    /* BIN format (2352 bytes data blocks) */
    cdd.sectorSize = 2352;
  }
  else
  {
    /* ISO format (2048 bytes data blocks) */
    cdd.sectorSize = 2048;
  }

  ret = (type == CT_BIN) ? 2352 : 2048;
  if (ret != cdd.sectorSize)
    elprintf(EL_STATUS|EL_ANOMALY, "cd: type detection mismatch");

  /* read CD image header + security code */
  pm_read(header + 0x10, 0x200, cdd.toc.tracks[0].fd);

  /* Simulate audio tracks if none found */
  if (cdd.toc.last == 1)
  {
    /* Some games require exact TOC infos */
    if (strstr(header + 0x180,"T-95035") != NULL)
    {
      /* Snatcher */
      cdd.toc.last = cdd.toc.end = 0;
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + toc_snatcher[cdd.toc.last];
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while (cdd.toc.last < 21);
    }
    else if (strstr(header + 0x180,"T-127015") != NULL)
    {
      /* Lunar - The Silver Star */
      cdd.toc.last = cdd.toc.end = 0;
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + toc_lunar[cdd.toc.last];
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while (cdd.toc.last < 52);
    }
    else if (strstr(header + 0x180,"T-113045") != NULL)
    {
      /* Shadow of the Beast II */
      cdd.toc.last = cdd.toc.end = 0;
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + toc_shadow[cdd.toc.last];
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while (cdd.toc.last < 15);
    }
    else if (strstr(header + 0x180,"T-143025") != NULL)
    {
      /* Dungeon Explorer */
      cdd.toc.last = cdd.toc.end = 0;
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + toc_dungeon[cdd.toc.last];
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while (cdd.toc.last < 13);
    }
    else if (strstr(header + 0x180,"MK-4410") != NULL)
    {
      /* Final Fight CD (USA, Europe) */
      cdd.toc.last = cdd.toc.end = 0;
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + toc_ffight[cdd.toc.last];
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while (cdd.toc.last < 26);
    }
    else if (strstr(header + 0x180,"G-6013") != NULL)
    {
      /* Final Fight CD (Japan) */
      cdd.toc.last = cdd.toc.end = 0;
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + toc_ffightj[cdd.toc.last];
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while (cdd.toc.last < 29);
    }
#if 0
    else
    {
      /* default TOC (99 tracks & 2s per audio tracks) */
      do
      {
        cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end + 2*75;
        cdd.toc.tracks[cdd.toc.last].end = cdd.toc.tracks[cdd.toc.last].start + 2*75;
        cdd.toc.end = cdd.toc.tracks[cdd.toc.last].end;
        cdd.toc.last++;
      }
      while ((cdd.toc.last < 99) && (cdd.toc.end < 56*60*75));
    }
#endif
  }

  /* Lead-out */
  cdd.toc.tracks[cdd.toc.last].start = cdd.toc.end;

  /* CD loaded */
  cdd.loaded = 1;

  /* disc not scanned yet */
  cdd.status = NO_DISC;

  return 0;
}