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
struct TYPE_5__ {unsigned int nb_slaves; int /*<<< orphan*/ * slaves; } ;
typedef  TYPE_1__ TeeContext ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int close_slave (int /*<<< orphan*/ *) ; 
 int tee_process_slave_failure (TYPE_2__*,unsigned int,int) ; 

__attribute__((used)) static int tee_write_trailer(AVFormatContext *avf)
{
    TeeContext *tee = avf->priv_data;
    int ret_all = 0, ret;
    unsigned i;

    for (i = 0; i < tee->nb_slaves; i++) {
        if ((ret = close_slave(&tee->slaves[i])) < 0) {
            ret = tee_process_slave_failure(avf, i, ret);
            if (!ret_all && ret < 0)
                ret_all = ret;
        }
    }
    av_freep(&tee->slaves);
    return ret_all;
}