#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dirty_pal; } ;
struct TYPE_7__ {TYPE_2__ video; TYPE_2__ vsram; TYPE_2__ cram; TYPE_2__ vram; } ;
struct TYPE_5__ {TYPE_2__ pal; TYPE_2__ dram; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKED_READ (int,...) ; 
 int /*<<< orphan*/  CHECKED_READ_BUFF (TYPE_2__) ; 
#define  CHUNK_32XPAL 134 
#define  CHUNK_32XSYS 133 
#define  CHUNK_CRAM 132 
#define  CHUNK_DRAM 131 
 char CHUNK_FM ; 
 char CHUNK_MISC_CD ; 
#define  CHUNK_VIDEO 130 
#define  CHUNK_VRAM 129 
#define  CHUNK_VSRAM 128 
 int PAHW_32X ; 
 int PAHW_MCD ; 
 TYPE_3__ Pico ; 
 TYPE_2__ Pico32x ; 
 TYPE_1__* Pico32xMem ; 
 int PicoAHW ; 
 int /*<<< orphan*/  R_ERROR_RETURN (char*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  areaEof (void*) ; 
 int /*<<< orphan*/  areaSeek (void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ g_read_offs ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int state_load_gfx(void *file)
{
  int ver, len, found = 0, to_find = 4;
  char buff[8];

  if (PicoAHW & PAHW_32X)
    to_find += 2;

  g_read_offs = 0;
  CHECKED_READ(8, buff);
  if (strncmp((char *)buff, "PicoSMCD", 8) && strncmp((char *)buff, "PicoSEXT", 8))
    R_ERROR_RETURN("bad header");
  CHECKED_READ(4, &ver);

  while (!areaEof(file) && found < to_find)
  {
    CHECKED_READ(1, buff);
    CHECKED_READ(4, &len);
    if (len < 0 || len > 1024*512) R_ERROR_RETURN("bad length");
    if (buff[0] > CHUNK_FM && buff[0] <= CHUNK_MISC_CD && !(PicoAHW & PAHW_MCD))
      R_ERROR_RETURN("cd chunk in non CD state?");

    switch (buff[0])
    {
      case CHUNK_VRAM:  CHECKED_READ_BUFF(Pico.vram);  found++; break;
      case CHUNK_CRAM:  CHECKED_READ_BUFF(Pico.cram);  found++; break;
      case CHUNK_VSRAM: CHECKED_READ_BUFF(Pico.vsram); found++; break;
      case CHUNK_VIDEO: CHECKED_READ_BUFF(Pico.video); found++; break;

#ifndef NO_32X
      case CHUNK_DRAM:
        if (Pico32xMem != NULL)
          CHECKED_READ_BUFF(Pico32xMem->dram);
        break;

      case CHUNK_32XPAL:
        if (Pico32xMem != NULL)
          CHECKED_READ_BUFF(Pico32xMem->pal);
        Pico32x.dirty_pal = 1;
        break;

      case CHUNK_32XSYS:
        CHECKED_READ_BUFF(Pico32x);
        break;
#endif
      default:
        areaSeek(file, len, SEEK_CUR);
        break;
    }
  }

out:
readend:
  return 0;
}