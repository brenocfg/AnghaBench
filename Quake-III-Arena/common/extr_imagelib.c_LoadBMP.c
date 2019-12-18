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
typedef  scalar_t__ qboolean ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char const*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetLittleLong (int /*<<< orphan*/ *) ; 
 int fgetLittleShort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

void LoadBMP (const char *filename, byte **pic, byte **palette, int *width, int *height)
{
	byte	*out;
	FILE	*fin;
	int		i;
    int		bfSize; 
    int		bfOffBits; 
	int		structSize;
    int		bcWidth; 
    int     bcHeight; 
    int	    bcPlanes; 
    int		bcBitCount; 
	byte	bcPalette[1024];
	qboolean	flipped;

	fin = fopen (filename, "rb");
	if (!fin) {
		Error ("Couldn't read %s", filename);
	}

	i = fgetLittleShort (fin);
	if (i != 'B' + ('M'<<8) ) {
		Error ("%s is not a bmp file", filename);
	}

	bfSize = fgetLittleLong (fin);
	fgetLittleShort(fin);
	fgetLittleShort(fin);
	bfOffBits = fgetLittleLong (fin);

	// the size will tell us if it is a
	// bitmapinfo or a bitmapcore
	structSize = fgetLittleLong (fin);
	if (structSize == 40) {
		// bitmapinfo
        bcWidth = fgetLittleLong(fin); 
        bcHeight= fgetLittleLong(fin); 
        bcPlanes = fgetLittleShort(fin); 
        bcBitCount = fgetLittleShort(fin); 

		fseek (fin, 24, SEEK_CUR);

		if (palette) {
			fread (bcPalette, 1, 1024, fin);
			*palette = malloc(768);

			for (i = 0 ; i < 256 ; i++) {
				(*palette)[i * 3 + 0] = bcPalette[i * 4 + 2];
				(*palette)[i * 3 + 1] = bcPalette[i * 4 + 1];
				(*palette)[i * 3 + 2] = bcPalette[i * 4 + 0];
			}
		}
	} else if (structSize == 12) {
		// bitmapcore
        bcWidth = fgetLittleShort(fin); 
        bcHeight= fgetLittleShort(fin); 
        bcPlanes = fgetLittleShort(fin); 
        bcBitCount = fgetLittleShort(fin); 

		if (palette) {
			fread (bcPalette, 1, 768, fin);
			*palette = malloc(768);

			for (i = 0 ; i < 256 ; i++) {
				(*palette)[i * 3 + 0] = bcPalette[i * 3 + 2];
				(*palette)[i * 3 + 1] = bcPalette[i * 3 + 1];
				(*palette)[i * 3 + 2] = bcPalette[i * 3 + 0];
			}
		}
	} else {
		Error ("%s had strange struct size", filename);
	}
	
	if (bcPlanes != 1) {
		Error ("%s was not a single plane image", filename);
	}

	if (bcBitCount != 8) {
		Error ("%s was not an 8 bit image", filename);
	}

	if (bcHeight < 0) {
		bcHeight = -bcHeight;
		flipped = qtrue;
	} else {
		flipped = qfalse;
	}

	if (width)
		*width = bcWidth;
	if (height)
		*height = bcHeight;

	if (!pic) {
		fclose (fin);
		return;
	}

	out = malloc ( bcWidth * bcHeight );
	*pic = out;
	fseek (fin, bfOffBits, SEEK_SET);

	if (flipped) {
		for (i = 0 ; i < bcHeight ; i++) {
			fread (out + bcWidth * (bcHeight - 1 - i), 1, bcWidth, fin);
		}
	} else {
		fread (out, 1, bcWidth*bcHeight, fin);
	}

	fclose (fin);
}