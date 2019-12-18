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
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int flags; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int circular_buffer_error; int /*<<< orphan*/  udp_fd; int /*<<< orphan*/  dest_addr_len; int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  is_connected; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; scalar_t__ fifo; } ;
typedef  TYPE_2__ UDPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fifo_generic_write (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int av_fifo_space (scalar_t__) ; 
 int ff_neterrno () ; 
 int ff_network_wait_fd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udp_write(URLContext *h, const uint8_t *buf, int size)
{
    UDPContext *s = h->priv_data;
    int ret;

#if HAVE_PTHREAD_CANCEL
    if (s->fifo) {
        uint8_t tmp[4];

        pthread_mutex_lock(&s->mutex);

        /*
          Return error if last tx failed.
          Here we can't know on which packet error was, but it needs to know that error exists.
        */
        if (s->circular_buffer_error<0) {
            int err=s->circular_buffer_error;
            pthread_mutex_unlock(&s->mutex);
            return err;
        }

        if(av_fifo_space(s->fifo) < size + 4) {
            /* What about a partial packet tx ? */
            pthread_mutex_unlock(&s->mutex);
            return AVERROR(ENOMEM);
        }
        AV_WL32(tmp, size);
        av_fifo_generic_write(s->fifo, tmp, 4, NULL); /* size of packet */
        av_fifo_generic_write(s->fifo, (uint8_t *)buf, size, NULL); /* the data */
        pthread_cond_signal(&s->cond);
        pthread_mutex_unlock(&s->mutex);
        return size;
    }
#endif
    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = ff_network_wait_fd(s->udp_fd, 1);
        if (ret < 0)
            return ret;
    }

    if (!s->is_connected) {
        ret = sendto (s->udp_fd, buf, size, 0,
                      (struct sockaddr *) &s->dest_addr,
                      s->dest_addr_len);
    } else
        ret = send(s->udp_fd, buf, size, 0);

    return ret < 0 ? ff_neterrno() : ret;
}