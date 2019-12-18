#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {TYPE_1__** streams; } ;
struct TYPE_4__ {int channels; int sample_rate; } ;
struct TYPE_3__ {TYPE_2__* codecpar; } ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */

__attribute__((used)) static int daud_write_header(struct AVFormatContext *s)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    if (par->channels!=6 || par->sample_rate!=96000)
        return -1;
    return 0;
}