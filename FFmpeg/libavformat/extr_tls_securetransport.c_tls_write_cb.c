#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_4__ {int /*<<< orphan*/  tcp; } ;
struct TYPE_6__ {int lastErr; TYPE_1__ tls_shared; } ;
typedef  TYPE_3__ TLSContext ;
typedef  scalar_t__ SSLConnectionRef ;
typedef  int /*<<< orphan*/  OSStatus ;

/* Variables and functions */
 int AVUNERROR (int) ; 
#define  EAGAIN 128 
 int /*<<< orphan*/  errSSLWouldBlock ; 
 int ffurl_write (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  ioErr ; 
 int /*<<< orphan*/  noErr ; 

__attribute__((used)) static OSStatus tls_write_cb(SSLConnectionRef connection, const void *data, size_t *dataLength)
{
    URLContext *h = (URLContext*)connection;
    TLSContext *c = h->priv_data;
    int written = ffurl_write(c->tls_shared.tcp, data, *dataLength);
    if (written <= 0) {
        *dataLength = 0;
        switch(AVUNERROR(written)) {
            case EAGAIN:
                return errSSLWouldBlock;
            default:
                c->lastErr = written;
                return ioErr;
        }
    } else {
        *dataLength = written;
        return noErr;
    }
}