#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {int /*<<< orphan*/  bdplus_handled; scalar_t__ bdplus_detected; int /*<<< orphan*/  libaacs_detected; int /*<<< orphan*/  aacs_handled; scalar_t__ aacs_detected; int /*<<< orphan*/  bluray_detected; } ;
struct TYPE_8__ {int /*<<< orphan*/  bd; } ;
typedef  TYPE_2__ BlurayContext ;
typedef  TYPE_3__ BLURAY_DISC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* bd_get_disc_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_disc_info(URLContext *h)
{
    BlurayContext *bd = h->priv_data;
    const BLURAY_DISC_INFO *disc_info;

    disc_info = bd_get_disc_info(bd->bd);
    if (!disc_info) {
        av_log(h, AV_LOG_ERROR, "bd_get_disc_info() failed\n");
        return -1;
    }

    if (!disc_info->bluray_detected) {
        av_log(h, AV_LOG_ERROR, "BluRay disc not detected\n");
        return -1;
    }

    /* AACS */
    if (disc_info->aacs_detected && !disc_info->aacs_handled) {
        if (!disc_info->libaacs_detected) {
            av_log(h, AV_LOG_ERROR,
                   "Media stream encrypted with AACS, install and configure libaacs\n");
        } else {
            av_log(h, AV_LOG_ERROR, "Your libaacs can't decrypt this media\n");
        }
        return -1;
    }

    /* BD+ */
    if (disc_info->bdplus_detected && !disc_info->bdplus_handled) {
        /*
        if (!disc_info->libbdplus_detected) {
            av_log(h, AV_LOG_ERROR,
                   "Media stream encrypted with BD+, install and configure libbdplus");
        } else {
        */
            av_log(h, AV_LOG_ERROR, "Unable to decrypt BD+ encrypted media\n");
        /*}*/
        return -1;
    }

    return 0;
}