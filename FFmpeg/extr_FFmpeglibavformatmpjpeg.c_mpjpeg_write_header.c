#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  boundary_tag; } ;
typedef  TYPE_1__ MPJPEGContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpjpeg_write_header(AVFormatContext *s)
{
    MPJPEGContext *mpj = s->priv_data;
    avio_printf(s->pb, "--%s\r\n", mpj->boundary_tag);
    avio_flush(s->pb);
    return 0;
}