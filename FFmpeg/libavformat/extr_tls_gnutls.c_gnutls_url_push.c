#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ssize_t ;
typedef  scalar_t__ gnutls_transport_ptr_t ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  errno ; 
 int ffurl_write (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static ssize_t gnutls_url_push(gnutls_transport_ptr_t transport,
                               const void *buf, size_t len)
{
    URLContext *h = (URLContext*) transport;
    int ret = ffurl_write(h, buf, len);
    if (ret >= 0)
        return ret;
    if (ret == AVERROR_EXIT)
        return 0;
    if (ret == AVERROR(EAGAIN))
        errno = EAGAIN;
    else
        errno = EIO;
    return -1;
}