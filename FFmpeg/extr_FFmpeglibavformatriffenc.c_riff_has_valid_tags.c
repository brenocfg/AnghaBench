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
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_MATCH_CASE ; 
 scalar_t__ av_dict_get (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__** riff_tags ; 

__attribute__((used)) static int riff_has_valid_tags(AVFormatContext *s)
{
    int i;

    for (i = 0; *riff_tags[i]; i++)
        if (av_dict_get(s->metadata, riff_tags[i], NULL, AV_DICT_MATCH_CASE))
            return 1;

    return 0;
}