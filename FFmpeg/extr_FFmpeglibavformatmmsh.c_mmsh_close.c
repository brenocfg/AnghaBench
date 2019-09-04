#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {int /*<<< orphan*/  asf_header; int /*<<< orphan*/  streams; scalar_t__ mms_hd; } ;
struct TYPE_6__ {TYPE_3__ mms; } ;
typedef  TYPE_2__ MMSHContext ;
typedef  TYPE_3__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_closep (scalar_t__*) ; 

__attribute__((used)) static int mmsh_close(URLContext *h)
{
    MMSHContext *mmsh = (MMSHContext *)h->priv_data;
    MMSContext *mms   = &mmsh->mms;
    if (mms->mms_hd)
        ffurl_closep(&mms->mms_hd);
    av_freep(&mms->streams);
    av_freep(&mms->asf_header);
    return 0;
}