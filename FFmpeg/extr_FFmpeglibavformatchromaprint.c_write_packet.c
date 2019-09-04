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
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ChromaprintMuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ chromaprint_feed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_packet(AVFormatContext *s, AVPacket *pkt)
{
    ChromaprintMuxContext *cpr = s->priv_data;
    return chromaprint_feed(cpr->ctx, pkt->data, pkt->size / 2) ? 0 : AVERROR(EINVAL);
}