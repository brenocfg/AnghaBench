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
struct TYPE_6__ {int /*<<< orphan*/  ssl_context; } ;
typedef  TYPE_2__ TLSContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int FFMIN (size_t,int) ; 
 int /*<<< orphan*/  SSLGetBufferedReadSize (int /*<<< orphan*/ ,size_t*) ; 
 int SSLRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,size_t*) ; 
 int map_ssl_error (int,size_t) ; 
 int print_tls_error (TYPE_1__*,int) ; 

__attribute__((used)) static int tls_read(URLContext *h, uint8_t *buf, int size)
{
    TLSContext *c = h->priv_data;
    size_t available = 0, processed = 0;
    int ret;
    SSLGetBufferedReadSize(c->ssl_context, &available);
    if (available)
        size = FFMIN(available, size);
    ret = SSLRead(c->ssl_context, buf, size, &processed);
    ret = map_ssl_error(ret, processed);
    if (ret > 0)
        return ret;
    if (ret == 0)
        return AVERROR_EOF;
    return print_tls_error(h, ret);
}