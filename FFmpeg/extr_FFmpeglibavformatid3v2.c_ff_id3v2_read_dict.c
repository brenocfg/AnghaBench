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
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  id3v2_read_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void ff_id3v2_read_dict(AVIOContext *pb, AVDictionary **metadata,
                        const char *magic, ID3v2ExtraMeta **extra_meta)
{
    id3v2_read_internal(pb, metadata, NULL, magic, extra_meta, 0);
}