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
struct TYPE_7__ {int /*<<< orphan*/  first_dts; TYPE_1__* codecpar; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 TYPE_2__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static AVStream *
add_dstream(AVFormatContext *s, AVStream *orig_st)
{
    AVStream *st;

    if (!(st = avformat_new_stream(s, NULL)))
        return NULL;
    st->id = orig_st->id;
    st->codecpar->codec_type = orig_st->codecpar->codec_type;
    st->first_dts         = orig_st->first_dts;

    return st;
}