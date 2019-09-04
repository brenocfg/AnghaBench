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
 int /*<<< orphan*/  printf (char*) ; 

void extract_voxel(char *lfile, char *rfile, char *prefix)
{
#ifdef OPENCV
    int w = 1920;
    int h = 1080;
    int shift = 0;
    int count = 0;
    CvCapture *lcap = cvCaptureFromFile(lfile);
    CvCapture *rcap = cvCaptureFromFile(rfile);
    while(1){
        image l = get_image_from_stream(lcap);
        image r = get_image_from_stream(rcap);
        if(!l.w || !r.w) break;
        if(count%100 == 0) {
            shift = best_3d_shift_r(l, r, -l.h/100, l.h/100);
            printf("%d\n", shift);
        }
        image ls = crop_image(l, (l.w - w)/2, (l.h - h)/2, w, h);
        image rs = crop_image(r, 105 + (r.w - w)/2, (r.h - h)/2 + shift, w, h);
        char buff[256];
        sprintf(buff, "%s_%05d_l", prefix, count);
        save_image(ls, buff);
        sprintf(buff, "%s_%05d_r", prefix, count);
        save_image(rs, buff);
        free_image(l);
        free_image(r);
        free_image(ls);
        free_image(rs);
        ++count;
    }

#else
    printf("need OpenCV for extraction\n");
#endif
}