#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iec61883_data {scalar_t__ packets; scalar_t__ max_packets; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_1__* queue_last; TYPE_1__* queue_first; } ;
struct TYPE_4__ {int len; struct TYPE_4__* next; scalar_t__ buf; } ;
typedef  TYPE_1__ DVPacket ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_malloc (scalar_t__) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iec61883_callback(unsigned char *data, int length,
                             int complete, void *callback_data)
{
    struct iec61883_data *dv = callback_data;
    DVPacket *packet;
    int ret;

#if THREADS
    pthread_mutex_lock(&dv->mutex);
#endif

    if (dv->packets >= dv->max_packets) {
        av_log(NULL, AV_LOG_ERROR, "DV packet queue overrun, dropping.\n");
        ret = 0;
        goto exit;
    }

    packet = av_mallocz(sizeof(*packet));
    if (!packet) {
        ret = -1;
        goto exit;
    }

    packet->buf = av_malloc(length + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!packet->buf) {
        av_free(packet);
        ret = -1;
        goto exit;
    }
    packet->len = length;

    memcpy(packet->buf, data, length);
    memset(packet->buf + length, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    if (dv->queue_first) {
        dv->queue_last->next = packet;
        dv->queue_last = packet;
    } else {
        dv->queue_first = packet;
        dv->queue_last = packet;
    }
    dv->packets++;

    ret = 0;

exit:
#if THREADS
    pthread_cond_broadcast(&dv->cond);
    pthread_mutex_unlock(&dv->mutex);
#endif
    return ret;
}