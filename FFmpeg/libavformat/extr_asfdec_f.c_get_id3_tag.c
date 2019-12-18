#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int /*<<< orphan*/  ff_id3v2_free_extra_meta (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_parse_apic (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_parse_chapters (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_id3v2_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void get_id3_tag(AVFormatContext *s, int len)
{
    ID3v2ExtraMeta *id3v2_extra_meta = NULL;

    ff_id3v2_read(s, ID3v2_DEFAULT_MAGIC, &id3v2_extra_meta, len);
    if (id3v2_extra_meta) {
        ff_id3v2_parse_apic(s, &id3v2_extra_meta);
        ff_id3v2_parse_chapters(s, &id3v2_extra_meta);
    }
    ff_id3v2_free_extra_meta(&id3v2_extra_meta);
}