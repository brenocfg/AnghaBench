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

__attribute__((used)) static void usage(void)
{
    printf("Show the relationships between rawvideo pixel formats and FourCC tags.\n");
    printf("usage: fourcc2pixfmt [OPTIONS]\n");
    printf("\n"
           "Options:\n"
           "-l                list the pixel format for each fourcc\n"
           "-L                list the fourccs for each pixel format\n"
           "-p PIX_FMT        given a pixel format, print the list of associated fourccs (one per line)\n"
           "-h                print this help\n");
}