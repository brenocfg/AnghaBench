#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int data; int xmin; int ymin; int xmax; int ymax; int hres; int vres; int bytes_per_line; int palette_type; int manufacturer; int version; int encoding; int bits_per_pixel; } ;
typedef  TYPE_1__ pcx_t ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,...) ; 
 void* LittleShort (int) ; 
 int LoadFile (char const*,void**) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void LoadPCX (const char *filename, byte **pic, byte **palette, int *width, int *height)
{
	byte	*raw;
	pcx_t	*pcx;
	int		x, y;
	int		len;
	int		dataByte, runLength;
	byte	*out, *pix;

	//
	// load the file
	//
	len = LoadFile (filename, (void **)&raw);

	//
	// parse the PCX file
	//
	pcx = (pcx_t *)raw;
	raw = &pcx->data;

	pcx->xmin = LittleShort(pcx->xmin);
	pcx->ymin = LittleShort(pcx->ymin);
	pcx->xmax = LittleShort(pcx->xmax);
	pcx->ymax = LittleShort(pcx->ymax);
	pcx->hres = LittleShort(pcx->hres);
	pcx->vres = LittleShort(pcx->vres);
	pcx->bytes_per_line = LittleShort(pcx->bytes_per_line);
	pcx->palette_type = LittleShort(pcx->palette_type);

	if (pcx->manufacturer != 0x0a
		|| pcx->version != 5
		|| pcx->encoding != 1
		|| pcx->bits_per_pixel != 8
		|| pcx->xmax >= 640
		|| pcx->ymax >= 480)
		Error ("Bad pcx file %s", filename);
	
	if (palette)
	{
		*palette = malloc(768);
		memcpy (*palette, (byte *)pcx + len - 768, 768);
	}

	if (width)
		*width = pcx->xmax+1;
	if (height)
		*height = pcx->ymax+1;

	if (!pic)
		return;

	out = malloc ( (pcx->ymax+1) * (pcx->xmax+1) );
	if (!out)
		Error ("Skin_Cache: couldn't allocate");

	*pic = out;

	pix = out;

	for (y=0 ; y<=pcx->ymax ; y++, pix += pcx->xmax+1)
	{
		for (x=0 ; x<=pcx->xmax ; )
		{
			dataByte = *raw++;

			if((dataByte & 0xC0) == 0xC0)
			{
				runLength = dataByte & 0x3F;
				dataByte = *raw++;
			}
			else
				runLength = 1;

			// FIXME: this shouldn't happen, but it does.  Are we decoding the file wrong?
			// Truncate runLength so we don't overrun the end of the buffer
			if ( ( y == pcx->ymax ) && ( x + runLength > pcx->xmax + 1 ) ) {
				runLength = pcx->xmax - x + 1;
			}

			while(runLength-- > 0)
				pix[x++] = dataByte;
		}

	}

	if ( raw - (byte *)pcx > len)
		Error ("PCX file %s was malformed", filename);

	free (pcx);
}