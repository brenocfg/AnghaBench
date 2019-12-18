#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ max_bitrate; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {scalar_t__ bit_rate; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVCPBProperties ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_DATA_CPB_PROPERTIES ; 
 scalar_t__ av_stream_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t get_stream_bit_rate(AVStream *stream)
{
    AVCPBProperties *props = (AVCPBProperties*)av_stream_get_side_data(
        stream,
        AV_PKT_DATA_CPB_PROPERTIES,
        NULL
    );

    if (stream->codecpar->bit_rate)
        return stream->codecpar->bit_rate;
    else if (props)
        return props->max_bitrate;

    return 0;
}