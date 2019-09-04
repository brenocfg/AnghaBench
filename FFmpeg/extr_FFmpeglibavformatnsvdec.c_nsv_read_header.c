#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nb_streams; TYPE_2__* priv_data; } ;
struct TYPE_11__ {scalar_t__ state; TYPE_1__* ahead; } ;
struct TYPE_10__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ NSVContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ NSV_FOUND_NSVF ; 
 scalar_t__ NSV_FOUND_NSVS ; 
 int NSV_MAX_RESYNC_TRIES ; 
 scalar_t__ NSV_UNSYNC ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int nsv_parse_NSVf_header (TYPE_3__*) ; 
 int nsv_parse_NSVs_header (TYPE_3__*) ; 
 int nsv_read_chunk (TYPE_3__*,int) ; 
 scalar_t__ nsv_resync (TYPE_3__*) ; 

__attribute__((used)) static int nsv_read_header(AVFormatContext *s)
{
    NSVContext *nsv = s->priv_data;
    int i, err;

    nsv->state = NSV_UNSYNC;
    nsv->ahead[0].data = nsv->ahead[1].data = NULL;

    for (i = 0; i < NSV_MAX_RESYNC_TRIES; i++) {
        if (nsv_resync(s) < 0)
            return -1;
        if (nsv->state == NSV_FOUND_NSVF) {
            err = nsv_parse_NSVf_header(s);
            if (err < 0)
                return err;
        }
            /* we need the first NSVs also... */
        if (nsv->state == NSV_FOUND_NSVS) {
            err = nsv_parse_NSVs_header(s);
            if (err < 0)
                return err;
            break; /* we just want the first one */
        }
    }
    if (s->nb_streams < 1) /* no luck so far */
        return -1;
    /* now read the first chunk, so we can attempt to decode more info */
    err = nsv_read_chunk(s, 1);

    av_log(s, AV_LOG_TRACE, "parsed header\n");
    return err;
}