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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 unsigned int ffio_read_varlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t get_fourcc(AVIOContext *bc)
{
    unsigned int len = ffio_read_varlen(bc);

    if (len == 2)
        return avio_rl16(bc);
    else if (len == 4)
        return avio_rl32(bc);
    else {
        av_log(NULL, AV_LOG_ERROR, "Unsupported fourcc length %d\n", len);
        return -1;
    }
}