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
typedef  int ulg ;
typedef  int /*<<< orphan*/  uch ;

/* Variables and functions */
 int /*<<< orphan*/  Trace (int /*<<< orphan*/ ) ; 
 int channels ; 
 int fread (int /*<<< orphan*/ *,long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int height ; 
 int /*<<< orphan*/ * image_data ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  saved_infile ; 
 int /*<<< orphan*/  stderr ; 
 int width ; 

uch *readpng_get_image(double display_exponent, int *pChannels, ulg *pRowbytes)
{
    ulg  rowbytes;


    /* expand palette images to RGB, low-bit-depth grayscale images to 8 bits,
     * transparency chunks to full alpha channel; strip 16-bit-per-sample
     * images to 8 bits per sample; and convert grayscale to RGB[A] */

    /* GRR WARNING:  grayscale needs to be expanded and channels reset! */

    *pRowbytes = rowbytes = channels*width;
    *pChannels = channels;

    if ((image_data = (uch *)malloc(rowbytes*height)) == NULL) {
        return NULL;
    }

    Trace((stderr, "readpng_get_image:  rowbytes = %ld, height = %ld\n", rowbytes, height));


    /* now we can go ahead and just read the whole image */

    if (fread(image_data, 1L, rowbytes*height, saved_infile) <
       rowbytes*height) {
        free (image_data);
        image_data = NULL;
        return NULL;
    }

    return image_data;
}