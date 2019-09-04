#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_id3v2_free_extra_meta (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_parse_apic (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_parse_chapters (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_id3(AVFormatContext *s, uint64_t id3pos)
{
    ID3v2ExtraMeta *id3v2_extra_meta = NULL;
    if (avio_seek(s->pb, id3pos, SEEK_SET) < 0)
        return;

    ff_id3v2_read(s, ID3v2_DEFAULT_MAGIC, &id3v2_extra_meta, 0);
    if (id3v2_extra_meta) {
        ff_id3v2_parse_apic(s, &id3v2_extra_meta);
        ff_id3v2_parse_chapters(s, &id3v2_extra_meta);
    }
    ff_id3v2_free_extra_meta(&id3v2_extra_meta);
}