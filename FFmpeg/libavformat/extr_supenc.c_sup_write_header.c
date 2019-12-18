#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nb_streams; int /*<<< orphan*/ * streams; TYPE_1__* oformat; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int sup_write_header(AVFormatContext *s)
{
    if (s->nb_streams != 1) {
        av_log(s, AV_LOG_ERROR, "%s files have exactly one stream\n",
               s->oformat->name);
        return AVERROR(EINVAL);
    }

    avpriv_set_pts_info(s->streams[0], 32, 1, 90000);

    return 0;
}