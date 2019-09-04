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
struct TYPE_3__ {int w; int h; int c; int* data; } ;
typedef  TYPE_1__ image ;
typedef  scalar_t__ IMTYPE ;

/* Variables and functions */
 scalar_t__ BMP ; 
 scalar_t__ JPG ; 
 scalar_t__ PNG ; 
 scalar_t__ TGA ; 
 unsigned char* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 int stbi_write_bmp (char*,int,int,int,unsigned char*) ; 
 int stbi_write_jpg (char*,int,int,int,unsigned char*,int) ; 
 int stbi_write_png (char*,int,int,int,unsigned char*,int) ; 
 int stbi_write_tga (char*,int,int,int,unsigned char*) ; 
 int /*<<< orphan*/  stderr ; 

void save_image_options(image im, const char *name, IMTYPE f, int quality)
{
    char buff[256];
    //sprintf(buff, "%s (%d)", name, windows);
    if(f == PNG)       sprintf(buff, "%s.png", name);
    else if (f == BMP) sprintf(buff, "%s.bmp", name);
    else if (f == TGA) sprintf(buff, "%s.tga", name);
    else if (f == JPG) sprintf(buff, "%s.jpg", name);
    else               sprintf(buff, "%s.png", name);
    unsigned char *data = calloc(im.w*im.h*im.c, sizeof(char));
    int i,k;
    for(k = 0; k < im.c; ++k){
        for(i = 0; i < im.w*im.h; ++i){
            data[i*im.c+k] = (unsigned char) (255*im.data[i + k*im.w*im.h]);
        }
    }
    int success = 0;
    if(f == PNG)       success = stbi_write_png(buff, im.w, im.h, im.c, data, im.w*im.c);
    else if (f == BMP) success = stbi_write_bmp(buff, im.w, im.h, im.c, data);
    else if (f == TGA) success = stbi_write_tga(buff, im.w, im.h, im.c, data);
    else if (f == JPG) success = stbi_write_jpg(buff, im.w, im.h, im.c, data, quality);
    free(data);
    if(!success) fprintf(stderr, "Failed to write image %s\n", buff);
}