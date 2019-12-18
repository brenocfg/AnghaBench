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
typedef  int /*<<< orphan*/  FreezeDetectContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int av_dict_set (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static int set_meta(FreezeDetectContext *s, AVFrame *frame, const char *key, const char *value)
{
    av_log(s, AV_LOG_INFO, "%s: %s\n", key, value);
    return av_dict_set(&frame->metadata, key, value, 0);
}