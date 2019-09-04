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
struct TYPE_4__ {int /*<<< orphan*/  umid; int /*<<< orphan*/  instance_number; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  umid_ul ; 

__attribute__((used)) static void mxf_write_umid(AVFormatContext *s, int type)
{
    MXFContext *mxf = s->priv_data;
    avio_write(s->pb, umid_ul, 13);
    avio_wb24(s->pb, mxf->instance_number);
    avio_write(s->pb, mxf->umid, 15);
    avio_w8(s->pb, type);
}