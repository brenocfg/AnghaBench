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
struct TYPE_5__ {TYPE_1__* fc; } ;
struct TYPE_4__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  event_flags; } ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMT_EVENT_FLAG_METADATA_UPDATED ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_metadata_int8_no_padding(MOVContext *c, AVIOContext *pb,
                                        unsigned len, const char *key)
{
    c->fc->event_flags |= AVFMT_EVENT_FLAG_METADATA_UPDATED;
    av_dict_set_int(&c->fc->metadata, key, avio_r8(pb), 0);

    return 0;
}