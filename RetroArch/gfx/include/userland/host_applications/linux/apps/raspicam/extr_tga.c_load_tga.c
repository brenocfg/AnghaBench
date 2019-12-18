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
struct TYPE_2__ {int bpp; int width; int height; } ;
struct tga_header {scalar_t__ image_type; scalar_t__ id_length; TYPE_1__ image_info; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char* malloc (int) ; 
 scalar_t__ read_header (int /*<<< orphan*/ *,struct tga_header*) ; 
 scalar_t__ tga_type_true_color ; 

unsigned char *load_tga(const char *filename, struct tga_header *header) {
    unsigned char *image = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp) {
        if(read_header(fp, header) == 0) {
            if (header->image_type == tga_type_true_color &&
                (header->image_info.bpp == 24 ||
                header->image_info.bpp == 32)) {
                int buflen = header->image_info.width *
                   header->image_info.height * (header->image_info.bpp / 8);
                image = malloc(buflen);
                if (image) {
                    if (header->id_length)
                        fseek(fp, SEEK_CUR, header->id_length);

                    if (fread(image, 1, buflen, fp) != buflen) {
                        free(image);
                        image = NULL;
                    }
                }
            }
        }
        fclose(fp);
    }
    return image;
}