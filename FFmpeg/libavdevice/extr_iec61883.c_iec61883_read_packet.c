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
struct iec61883_data {int (* parse_queue ) (struct iec61883_data*,int /*<<< orphan*/ *) ;int receive_error; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  eof; } ;
struct TYPE_3__ {struct iec61883_data* priv_data; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  iec61883_receive_task (void*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct iec61883_data*,int /*<<< orphan*/ *) ; 
 int stub2 (struct iec61883_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iec61883_read_packet(AVFormatContext *context, AVPacket *pkt)
{
    struct iec61883_data *dv = context->priv_data;
    int size;

    /**
     * Try to parse frames from queue
     */

#if THREADS
    pthread_mutex_lock(&dv->mutex);
    while ((size = dv->parse_queue(dv, pkt)) == -1)
        if (!dv->eof)
            pthread_cond_wait(&dv->cond, &dv->mutex);
        else
            break;
    pthread_mutex_unlock(&dv->mutex);
#else
    int result;
    while ((size = dv->parse_queue(dv, pkt)) == -1) {
        iec61883_receive_task((void *)dv);
        if (dv->receive_error)
            return dv->receive_error;
    }
#endif

    return size;
}