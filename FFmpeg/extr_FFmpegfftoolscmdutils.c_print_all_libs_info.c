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
 int /*<<< orphan*/  AVCODEC ; 
 int /*<<< orphan*/  AVDEVICE ; 
 int /*<<< orphan*/  AVFILTER ; 
 int /*<<< orphan*/  AVFORMAT ; 
 int /*<<< orphan*/  AVRESAMPLE ; 
 int /*<<< orphan*/  AVUTIL ; 
 int /*<<< orphan*/  POSTPROC ; 
 int /*<<< orphan*/  PRINT_LIB_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SWRESAMPLE ; 
 int /*<<< orphan*/  SWSCALE ; 
 int /*<<< orphan*/  avcodec ; 
 int /*<<< orphan*/  avdevice ; 
 int /*<<< orphan*/  avfilter ; 
 int /*<<< orphan*/  avformat ; 
 int /*<<< orphan*/  avresample ; 
 int /*<<< orphan*/  avutil ; 
 int /*<<< orphan*/  postproc ; 
 int /*<<< orphan*/  swresample ; 
 int /*<<< orphan*/  swscale ; 

__attribute__((used)) static void print_all_libs_info(int flags, int level)
{
    PRINT_LIB_INFO(avutil,     AVUTIL,     flags, level);
    PRINT_LIB_INFO(avcodec,    AVCODEC,    flags, level);
    PRINT_LIB_INFO(avformat,   AVFORMAT,   flags, level);
    PRINT_LIB_INFO(avdevice,   AVDEVICE,   flags, level);
    PRINT_LIB_INFO(avfilter,   AVFILTER,   flags, level);
    PRINT_LIB_INFO(avresample, AVRESAMPLE, flags, level);
    PRINT_LIB_INFO(swscale,    SWSCALE,    flags, level);
    PRINT_LIB_INFO(swresample, SWRESAMPLE, flags, level);
    PRINT_LIB_INFO(postproc,   POSTPROC,   flags, level);
}