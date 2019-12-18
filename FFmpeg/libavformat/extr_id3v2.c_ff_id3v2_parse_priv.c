#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  ID3v2ExtraMeta ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int ff_id3v2_parse_priv_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int ff_id3v2_parse_priv(AVFormatContext *s, ID3v2ExtraMeta **extra_meta)
{
    return ff_id3v2_parse_priv_dict(&s->metadata, extra_meta);
}