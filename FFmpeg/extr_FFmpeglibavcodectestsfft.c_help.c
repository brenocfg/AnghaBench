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
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void help(void)
{
    av_log(NULL, AV_LOG_INFO,
           "usage: fft-test [-h] [-s] [-i] [-n b]\n"
           "-h     print this help\n"
           "-s     speed test\n"
           "-m     (I)MDCT test\n"
           "-d     (I)DCT test\n"
           "-r     (I)RDFT test\n"
           "-i     inverse transform test\n"
           "-n b   set the transform size to 2^b\n"
           "-f x   set scale factor for output data of (I)MDCT to x\n");
}