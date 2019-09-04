#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_7__ {int (* io_open ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int nb_extra_packets; int** extra_packets; int /*<<< orphan*/ * extra_packet_sizes; int /*<<< orphan*/  out; int /*<<< orphan*/  temp_filename; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_WB24 (int*,int) ; 
 int /*<<< orphan*/  MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_file(AVFormatContext *s, OutputStream *os, int64_t start_ts)
{
    int ret, i;
    ret = s->io_open(s, &os->out, os->temp_filename, AVIO_FLAG_WRITE, NULL);
    if (ret < 0)
        return ret;
    avio_wb32(os->out, 0);
    avio_wl32(os->out, MKTAG('m','d','a','t'));
    for (i = 0; i < os->nb_extra_packets; i++) {
        AV_WB24(os->extra_packets[i] + 4, start_ts);
        os->extra_packets[i][7] = (start_ts >> 24) & 0x7f;
        avio_write(os->out, os->extra_packets[i], os->extra_packet_sizes[i]);
    }
    return 0;
}