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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int avpriv_dict_set_timestamp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ff_parse_creation_time_metadata (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ff_standardize_creation_time(AVFormatContext *s)
{
    int64_t timestamp;
    int ret = ff_parse_creation_time_metadata(s, &timestamp, 0);
    if (ret == 1)
        return avpriv_dict_set_timestamp(&s->metadata, "creation_time", timestamp);
    return ret;
}