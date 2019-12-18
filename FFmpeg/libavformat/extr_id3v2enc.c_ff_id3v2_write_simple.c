#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int /*<<< orphan*/  metadata_header_padding; int /*<<< orphan*/  pb; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ID3v2EncContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_id3v2_finish (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_id3v2_start (TYPE_1__*,int /*<<< orphan*/ ,int,char const*) ; 
 int ff_id3v2_write_metadata (struct AVFormatContext*,TYPE_1__*) ; 

int ff_id3v2_write_simple(struct AVFormatContext *s, int id3v2_version,
                          const char *magic)
{
    ID3v2EncContext id3 = { 0 };
    int ret;

    ff_id3v2_start(&id3, s->pb, id3v2_version, magic);
    if ((ret = ff_id3v2_write_metadata(s, &id3)) < 0)
        return ret;
    ff_id3v2_finish(&id3, s->pb, s->metadata_header_padding);

    return 0;
}