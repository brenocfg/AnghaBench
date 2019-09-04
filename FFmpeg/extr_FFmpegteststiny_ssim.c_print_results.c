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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,double,double,double,double,...) ; 
 double ssd_to_psnr (int,int) ; 
 double ssim_db (double,int) ; 

__attribute__((used)) static void print_results(uint64_t ssd[3], double ssim[3], int frames, int w, int h)
{
    printf( "PSNR Y:%.3f  U:%.3f  V:%.3f  All:%.3f | ",
            ssd_to_psnr( ssd[0], (uint64_t)frames*w*h ),
            ssd_to_psnr( ssd[1], (uint64_t)frames*w*h/4 ),
            ssd_to_psnr( ssd[2], (uint64_t)frames*w*h/4 ),
            ssd_to_psnr( ssd[0] + ssd[1] + ssd[2], (uint64_t)frames*w*h*3/2 ) );
    printf( "SSIM Y:%.5f U:%.5f V:%.5f All:%.5f (%.5f)",
            ssim[0] / frames,
            ssim[1] / frames,
            ssim[2] / frames,
            (ssim[0]*4 + ssim[1] + ssim[2]) / (frames*6),
            ssim_db(ssim[0] * 4 + ssim[1] + ssim[2], frames*6));
}