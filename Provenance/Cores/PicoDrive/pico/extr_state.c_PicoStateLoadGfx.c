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
struct TYPE_2__ {int /*<<< orphan*/  video; int /*<<< orphan*/ * vsram; int /*<<< orphan*/ * cram; int /*<<< orphan*/ * vram; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  areaClose (void*) ; 
 int /*<<< orphan*/  areaRead (int /*<<< orphan*/ *,int,int,void*) ; 
 int /*<<< orphan*/  areaSeek (void*,int,int /*<<< orphan*/ ) ; 
 void* open_save_file (char const*,int /*<<< orphan*/ ) ; 
 int state_load_gfx (void*) ; 

int PicoStateLoadGfx(const char *fname)
{
  void *afile;
  int ret;

  afile = open_save_file(fname, 0);
  if (afile == NULL)
    return -1;

  ret = state_load_gfx(afile);
  if (ret != 0) {
    // assume legacy
    areaSeek(afile, 0x10020, SEEK_SET);  // skip header and RAM
    areaRead(Pico.vram, 1, sizeof(Pico.vram), afile);
    areaSeek(afile, 0x2000, SEEK_CUR);
    areaRead(Pico.cram, 1, sizeof(Pico.cram), afile);
    areaRead(Pico.vsram, 1, sizeof(Pico.vsram), afile);
    areaSeek(afile, 0x221a0, SEEK_SET);
    areaRead(&Pico.video, 1, sizeof(Pico.video), afile);
  }
  areaClose(afile);
  return 0;
}