#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int revents; } ;
struct iec61883_data {int receiving; int eof; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  raw1394; TYPE_1__ raw1394_poll; int /*<<< orphan*/  receive_error; scalar_t__ thread_loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EIO ; 
 int POLLIN ; 
 int POLLPRI ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int poll (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw1394_loop_iterate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *iec61883_receive_task(void *opaque)
{
    struct iec61883_data *dv = (struct iec61883_data *)opaque;
    int result;

#if THREADS
    while (dv->thread_loop)
#endif
    {
        while ((result = poll(&dv->raw1394_poll, 1, 200)) < 0) {
            if (!(errno == EAGAIN || errno == EINTR)) {
                av_log(NULL, AV_LOG_ERROR, "Raw1394 poll error occurred.\n");
                dv->receive_error = AVERROR(EIO);
                return NULL;
            }
        }
        if (result > 0 && ((dv->raw1394_poll.revents & POLLIN)
                           || (dv->raw1394_poll.revents & POLLPRI))) {
            dv->receiving = 1;
            raw1394_loop_iterate(dv->raw1394);
        } else if (dv->receiving) {
            av_log(NULL, AV_LOG_ERROR, "No more input data available\n");
#if THREADS
            pthread_mutex_lock(&dv->mutex);
            dv->eof = 1;
            pthread_cond_broadcast(&dv->cond);
            pthread_mutex_unlock(&dv->mutex);
#else
            dv->eof = 1;
#endif
            return NULL;
        }
    }

    return NULL;
}