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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int NEEDS_CHECKING ; 
 double av_int2double (int /*<<< orphan*/ ) ; 
 double av_int2float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ebml_read_float(AVIOContext *pb, int size, double *num)
{
    if (size == 0)
        *num = 0;
    else if (size == 4)
        *num = av_int2float(avio_rb32(pb));
    else if (size == 8)
        *num = av_int2double(avio_rb64(pb));
    else
        return AVERROR_INVALIDDATA;

    return NEEDS_CHECKING;
}