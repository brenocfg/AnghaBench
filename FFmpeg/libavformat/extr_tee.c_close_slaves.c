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
struct TYPE_4__ {unsigned int nb_slaves; int /*<<< orphan*/ * slaves; } ;
typedef  TYPE_1__ TeeContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  close_slave (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_slaves(AVFormatContext *avf)
{
    TeeContext *tee = avf->priv_data;
    unsigned i;

    for (i = 0; i < tee->nb_slaves; i++) {
        close_slave(&tee->slaves[i]);
    }
    av_freep(&tee->slaves);
}