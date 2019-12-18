#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ FlacEncodeContext ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_frame_footer (TYPE_1__*) ; 
 int /*<<< orphan*/  write_frame_header (TYPE_1__*) ; 
 int /*<<< orphan*/  write_subframes (TYPE_1__*) ; 

__attribute__((used)) static int write_frame(FlacEncodeContext *s, AVPacket *avpkt)
{
    init_put_bits(&s->pb, avpkt->data, avpkt->size);
    write_frame_header(s);
    write_subframes(s);
    write_frame_footer(s);
    return put_bits_count(&s->pb) >> 3;
}