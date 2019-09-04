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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int logical_pos; int io_error; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond_wakeup_background; int /*<<< orphan*/  cond_wakeup_main; scalar_t__ io_eof_reached; int /*<<< orphan*/  ring; } ;
typedef  int /*<<< orphan*/  RingBuffer ;
typedef  TYPE_2__ Context ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_EXIT ; 
 int FFMIN (int,int) ; 
 scalar_t__ async_check_interrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_generic_read (int /*<<< orphan*/ *,void*,int,void (*) (void*,void*,int)) ; 
 int ring_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int async_read_internal(URLContext *h, void *dest, int size, int read_complete,
                               void (*func)(void*, void*, int))
{
    Context      *c       = h->priv_data;
    RingBuffer   *ring    = &c->ring;
    int           to_read = size;
    int           ret     = 0;

    pthread_mutex_lock(&c->mutex);

    while (to_read > 0) {
        int fifo_size, to_copy;
        if (async_check_interrupt(h)) {
            ret = AVERROR_EXIT;
            break;
        }
        fifo_size = ring_size(ring);
        to_copy   = FFMIN(to_read, fifo_size);
        if (to_copy > 0) {
            ring_generic_read(ring, dest, to_copy, func);
            if (!func)
                dest = (uint8_t *)dest + to_copy;
            c->logical_pos += to_copy;
            to_read        -= to_copy;
            ret             = size - to_read;

            if (to_read <= 0 || !read_complete)
                break;
        } else if (c->io_eof_reached) {
            if (ret <= 0) {
                if (c->io_error)
                    ret = c->io_error;
                else
                    ret = AVERROR_EOF;
            }
            break;
        }
        pthread_cond_signal(&c->cond_wakeup_background);
        pthread_cond_wait(&c->cond_wakeup_main, &c->mutex);
    }

    pthread_cond_signal(&c->cond_wakeup_background);
    pthread_mutex_unlock(&c->mutex);

    return ret;
}