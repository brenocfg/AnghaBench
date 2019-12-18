#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int colornumber; int charaddr; int coloroffset; int paladdr; int (* PostPixelFetchCalc ) (TYPE_1__*,int) ;int /*<<< orphan*/  priority; int /*<<< orphan*/  transparencyenable; } ;
typedef  TYPE_1__ vdp2draw_struct ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_10__ {int pixeloffset; int ystart; int yend; int xstart; int xend; int lineincrement; } ;
typedef  TYPE_2__ clipping_struct ;

/* Variables and functions */
 int /*<<< orphan*/  HandleClipping (TYPE_1__*,TYPE_2__*) ; 
 int SAT2YAB1 (int) ; 
 int T1ReadByte (int /*<<< orphan*/ ,int) ; 
 int T1ReadLong (int /*<<< orphan*/ ,int) ; 
 int T1ReadWord (int /*<<< orphan*/ ,int) ; 
 int Vdp2ColorRamGetColor (int) ; 
 int /*<<< orphan*/  Vdp2Ram ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 (TYPE_1__*,int) ; 
 int stub2 (TYPE_1__*,int) ; 
 int stub3 (TYPE_1__*,int) ; 
 int* vdp2_fb ; 
 int /*<<< orphan*/ ** vdp2_prio ; 
 int /*<<< orphan*/  vdp2putpixel (int,int,int,int /*<<< orphan*/ ) ; 
 int vdp2width ; 

void Vdp2DrawScrollBitmap(vdp2draw_struct *info)
{
    int i, i2;
    clipping_struct clip;

    HandleClipping(info, &clip);

    switch (info->colornumber)
    {
        case 0: // 4 BPP(16 colors)
                // fix me
            printf("vdp2 bitmap 4 bpp draw\n");
            return;
        case 1: // 8 BPP(256 colors)
            info->charaddr += clip.pixeloffset;

            for (i = clip.ystart; i < clip.yend; i++)
            {
                for (i2 = clip.xstart; i2 < clip.xend; i2++)
                {
                    u16 color = T1ReadByte(Vdp2Ram, info->charaddr);
                    info->charaddr++;

                    if (color == 0 && info->transparencyenable) {
                        vdp2putpixel(i2, i, 0, info->priority);
                    }
                    else    {
                        color = Vdp2ColorRamGetColor(info->coloroffset + (info->paladdr | color));
                        vdp2putpixel(i2, i, info->PostPixelFetchCalc(info, color) | 0x8000, info->priority);
                    }
                }

                info->charaddr += clip.lineincrement;
            }

            return;
        case 2:
            printf("vdp2 bitmap 16bpp palette draw\n");
            break;
        case 3: // 15 BPP
            clip.pixeloffset *= 2;
            clip.lineincrement *= 2;

            info->charaddr += clip.pixeloffset;

            for (i = clip.ystart; i < clip.yend; i++)
            {
                for (i2 = clip.xstart; i2 < clip.xend; i2++)
                {
                    u16 color = T1ReadWord(Vdp2Ram, info->charaddr);
                    info->charaddr += 2;

                    if ((color & 0x8000) == 0 && info->transparencyenable)
                        vdp2_fb[(i * vdp2width) + i2] = 0;
                    else
                        vdp2_fb[(i * vdp2width) + i2] = info->PostPixelFetchCalc(info, SAT2YAB1(color)) | 0x8000;

                    vdp2_prio[i][i2] = info->priority;
                }

                info->charaddr += clip.lineincrement;
            }

            return;
        case 4: // 24 BPP
            clip.pixeloffset *= 4;
            clip.lineincrement *= 4;

            info->charaddr += clip.pixeloffset;

            for (i = clip.ystart; i < clip.yend; i++)
            {
                for (i2 = clip.xstart; i2 < clip.xend; i2++)
                {
                    u32 color = T1ReadLong(Vdp2Ram, info->charaddr);
                    info->charaddr += 4;

                    if ((color & 0x80000000) == 0 && info->transparencyenable)
                        vdp2putpixel(i2, i, 0, info->priority);
                    else    {
                        u16 dot = ((color & 0xF80000) >> 19 |
                                   (color & 0x00F800) >> 6 |
                                   (color & 0x0000F8) << 7 | 0x8000);
                        vdp2putpixel(i2, i, info->PostPixelFetchCalc(info, dot), info->priority);
                    }
                }

                info->charaddr += clip.lineincrement;

            }
            return;
        default: break;
    }
}