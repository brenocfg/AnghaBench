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
typedef  int /*<<< orphan*/  image ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_error (char*) ; 
 int /*<<< orphan*/  find_replace (char*,char*,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  free_image (int /*<<< orphan*/ ) ; 
 int fscanf (int /*<<< orphan*/ *,char*,int*,char*) ; 
 int /*<<< orphan*/  load_rle (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  make_image (int,int,int) ; 
 int /*<<< orphan*/  or_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* read_intlist (char*,int*,int /*<<< orphan*/ ) ; 

image get_segmentation_image(char *path, int w, int h, int classes)
{
    char labelpath[4096];
    find_replace(path, "images", "mask", labelpath);
    find_replace(labelpath, "JPEGImages", "mask", labelpath);
    find_replace(labelpath, ".jpg", ".txt", labelpath);
    find_replace(labelpath, ".JPG", ".txt", labelpath);
    find_replace(labelpath, ".JPEG", ".txt", labelpath);
    image mask = make_image(w, h, classes);
    FILE *file = fopen(labelpath, "r");
    if(!file) file_error(labelpath);
    char buff[32788];
    int id;
    image part = make_image(w, h, 1);
    while(fscanf(file, "%d %s", &id, buff) == 2){
        int n = 0;
        int *rle = read_intlist(buff, &n, 0);
        load_rle(part, rle, n);
        or_image(part, mask, id);
        free(rle);
    }
    //exclusive_image(mask);
    fclose(file);
    free_image(part);
    return mask;
}