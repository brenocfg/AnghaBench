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
struct TYPE_5__ {int /*<<< orphan*/  MaxFALL; int /*<<< orphan*/  MaxCLL; } ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  TYPE_2__ AVContentLightMetadata ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_content_light_metadata(AVFilterContext *ctx, AVFrameSideData *sd)
{
    AVContentLightMetadata* metadata = (AVContentLightMetadata*)sd->data;

    av_log(ctx, AV_LOG_INFO, "Content Light Level information: "
           "MaxCLL=%d, MaxFALL=%d",
           metadata->MaxCLL, metadata->MaxFALL);
}