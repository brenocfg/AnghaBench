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

/* Variables and functions */
 int /*<<< orphan*/  DrawSprite (scalar_t__,int) ; 
 scalar_t__ HighPreSpr ; 
 int PDRAW_DIRTY_SPRITES ; 
 int PDRAW_SPRITES_MOVED ; 
 int /*<<< orphan*/  PrepareSprites (int) ; 
 int rendstatus ; 

__attribute__((used)) static void DrawAllSprites(unsigned char *sprited, int prio, int sh)
{
  int rs = rendstatus;
  unsigned char *p;
  int cnt;

  if (rs & (PDRAW_SPRITES_MOVED|PDRAW_DIRTY_SPRITES)) {
    //elprintf(EL_STATUS, "PrepareSprites(%i)", (rs>>4)&1);
    PrepareSprites(rs & PDRAW_DIRTY_SPRITES);
    rendstatus = rs & ~(PDRAW_SPRITES_MOVED|PDRAW_DIRTY_SPRITES);
  }

  cnt = sprited[0] & 0x7f;
  if (cnt == 0) return;

  p = &sprited[3];

  // Go through sprites backwards:
  for (cnt--; cnt >= 0; cnt--)
  {
    int offs;
    if ((p[cnt] >> 7) != prio) continue;
    offs = (p[cnt]&0x7f) * 2;
    DrawSprite(HighPreSpr + offs, sh);
  }
}