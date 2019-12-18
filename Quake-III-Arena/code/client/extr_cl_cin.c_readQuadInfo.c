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
typedef  int byte ;
struct TYPE_6__ {scalar_t__ linbuf; } ;
struct TYPE_5__ {int xsize; int ysize; int maxsize; int minsize; int CIN_HEIGHT; int CIN_WIDTH; int samplesPerLine; int samplesPerPixel; int screenDelta; unsigned int* t; int drawX; int drawY; int /*<<< orphan*/  VQBuffer; int /*<<< orphan*/  VQ1; int /*<<< orphan*/  VQNormal; int /*<<< orphan*/  VQ0; void* smootheddouble; void* half; } ;
struct TYPE_4__ {scalar_t__ hardwareType; int maxTextureSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 scalar_t__ GLHW_RAGEPRO ; 
 TYPE_3__ cin ; 
 TYPE_2__* cinTable ; 
 size_t currentHandle ; 
 TYPE_1__ glConfig ; 
 void* qfalse ; 

__attribute__((used)) static void readQuadInfo( byte *qData )
{
	if (currentHandle < 0) return;

	cinTable[currentHandle].xsize    = qData[0]+qData[1]*256;
	cinTable[currentHandle].ysize    = qData[2]+qData[3]*256;
	cinTable[currentHandle].maxsize  = qData[4]+qData[5]*256;
	cinTable[currentHandle].minsize  = qData[6]+qData[7]*256;
	
	cinTable[currentHandle].CIN_HEIGHT = cinTable[currentHandle].ysize;
	cinTable[currentHandle].CIN_WIDTH  = cinTable[currentHandle].xsize;

	cinTable[currentHandle].samplesPerLine = cinTable[currentHandle].CIN_WIDTH*cinTable[currentHandle].samplesPerPixel;
	cinTable[currentHandle].screenDelta = cinTable[currentHandle].CIN_HEIGHT*cinTable[currentHandle].samplesPerLine;

	cinTable[currentHandle].half = qfalse;
	cinTable[currentHandle].smootheddouble = qfalse;
	
	cinTable[currentHandle].VQ0 = cinTable[currentHandle].VQNormal;
	cinTable[currentHandle].VQ1 = cinTable[currentHandle].VQBuffer;

	cinTable[currentHandle].t[0] = (0 - (unsigned int)cin.linbuf)+(unsigned int)cin.linbuf+cinTable[currentHandle].screenDelta;
	cinTable[currentHandle].t[1] = (0 - ((unsigned int)cin.linbuf + cinTable[currentHandle].screenDelta))+(unsigned int)cin.linbuf;

        cinTable[currentHandle].drawX = cinTable[currentHandle].CIN_WIDTH;
        cinTable[currentHandle].drawY = cinTable[currentHandle].CIN_HEIGHT;
        
	// rage pro is very slow at 512 wide textures, voodoo can't do it at all
	if ( glConfig.hardwareType == GLHW_RAGEPRO || glConfig.maxTextureSize <= 256) {
                if (cinTable[currentHandle].drawX>256) {
                        cinTable[currentHandle].drawX = 256;
                }
                if (cinTable[currentHandle].drawY>256) {
                        cinTable[currentHandle].drawY = 256;
                }
		if (cinTable[currentHandle].CIN_WIDTH != 256 || cinTable[currentHandle].CIN_HEIGHT != 256) {
			Com_Printf("HACK: approxmimating cinematic for Rage Pro or Voodoo\n");
		}
	}
#if defined(MACOS_X)
	cinTable[currentHandle].drawX = 256;
	cinTable[currentHandle].drawX = 256;
#endif
}