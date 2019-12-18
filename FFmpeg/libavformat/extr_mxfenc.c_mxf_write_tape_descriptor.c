#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* pb; } ;
struct TYPE_9__ {scalar_t__ buf_ptr; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_KEY (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  TapeDescriptor ; 
 int /*<<< orphan*/  klv_encode_ber_length (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mxf_write_local_tag (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  mxf_write_metadata_key (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mxf_write_uuid (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxf_write_tape_descriptor(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;

    mxf_write_metadata_key(pb, 0x012e00);
    PRINT_KEY(s, "tape descriptor key", pb->buf_ptr - 16);
    klv_encode_ber_length(pb, 20);
    mxf_write_local_tag(pb, 16, 0x3C0A);
    mxf_write_uuid(pb, TapeDescriptor, 0);
    PRINT_KEY(s, "tape_desc uid", pb->buf_ptr - 16);
}