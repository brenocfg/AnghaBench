#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_10__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_9__ {int /*<<< orphan*/  asf_header_size; int /*<<< orphan*/  asf_header_read_size; } ;
struct TYPE_11__ {TYPE_1__ mms; int /*<<< orphan*/  location; } ;
typedef  TYPE_3__ MMSHContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 TYPE_3__* av_mallocz (int) ; 
 int /*<<< orphan*/  mmsh_close (TYPE_2__*) ; 
 int mmsh_open_internal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t mmsh_read_seek(URLContext *h, int stream_index,
                        int64_t timestamp, int flags)
{
    MMSHContext *mmsh_old = h->priv_data;
    MMSHContext *mmsh     = av_mallocz(sizeof(*mmsh));
    int ret;

    if (!mmsh)
        return AVERROR(ENOMEM);

    h->priv_data = mmsh;
    ret= mmsh_open_internal(h, mmsh_old->location, 0, FFMAX(timestamp, 0), 0);
    if(ret>=0){
        h->priv_data = mmsh_old;
        mmsh_close(h);
        h->priv_data = mmsh;
        av_free(mmsh_old);
        mmsh->mms.asf_header_read_size = mmsh->mms.asf_header_size;
    }else {
        h->priv_data = mmsh_old;
        av_free(mmsh);
    }

    return ret;
}