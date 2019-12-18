#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  id3v2_read_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ **,unsigned int) ; 

void ff_id3v2_read(AVFormatContext *s, const char *magic,
                   ID3v2ExtraMeta **extra_meta, unsigned int max_search_size)
{
    id3v2_read_internal(s->pb, &s->metadata, s, magic, extra_meta, max_search_size);
}