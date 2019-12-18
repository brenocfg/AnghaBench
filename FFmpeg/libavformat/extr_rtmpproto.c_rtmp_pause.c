#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int /*<<< orphan*/  last_timestamp; } ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int gen_pause (TYPE_1__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtmp_pause(URLContext *s, int pause)
{
    RTMPContext *rt = s->priv_data;
    int ret;
    av_log(s, AV_LOG_DEBUG, "Pause at timestamp %d\n",
           rt->last_timestamp);
    if ((ret = gen_pause(s, rt, pause, rt->last_timestamp)) < 0) {
        av_log(s, AV_LOG_ERROR, "Unable to send pause command at timestamp %d\n",
               rt->last_timestamp);
        return ret;
    }
    return 0;
}