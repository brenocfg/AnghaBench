#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {int flags; TYPE_4__* priv_data; } ;
typedef  TYPE_3__ URLContext ;
struct TYPE_8__ {TYPE_1__* tcp; } ;
struct TYPE_10__ {int /*<<< orphan*/  session; TYPE_2__ tls_shared; } ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_4__ TLSContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVIO_FLAG_NONBLOCK ; 
 int gnutls_record_send (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int print_tls_error (TYPE_3__*,int) ; 

__attribute__((used)) static int tls_write(URLContext *h, const uint8_t *buf, int size)
{
    TLSContext *c = h->priv_data;
    int ret;
    // Set or clear the AVIO_FLAG_NONBLOCK on c->tls_shared.tcp
    c->tls_shared.tcp->flags &= ~AVIO_FLAG_NONBLOCK;
    c->tls_shared.tcp->flags |= h->flags & AVIO_FLAG_NONBLOCK;
    ret = gnutls_record_send(c->session, buf, size);
    if (ret > 0)
        return ret;
    if (ret == 0)
        return AVERROR_EOF;
    return print_tls_error(h, ret);
}