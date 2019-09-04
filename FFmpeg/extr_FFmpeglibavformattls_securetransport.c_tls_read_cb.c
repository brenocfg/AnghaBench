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
#define  EAGAIN 130 
#define  ECONNRESET 129 
#define  ENOENT 128 
 int /*<<< orphan*/  errSSLClosedAbort ; 
 int /*<<< orphan*/  errSSLClosedGraceful ; 
 int /*<<< orphan*/  errSSLWouldBlock ; 
 int ffurl_read (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  ioErr ; 
 int /*<<< orphan*/  noErr ; 

__attribute__((used)) static OSStatus tls_read_cb(SSLConnectionRef connection, void *data, size_t *dataLength)
{
    URLContext *h = (URLContext*)connection;
    TLSContext *c = h->priv_data;
    size_t requested = *dataLength;
    int read = ffurl_read(c->tls_shared.tcp, data, requested);
    if (read <= 0) {
        *dataLength = 0;
        switch(AVUNERROR(read)) {
            case ENOENT:
            case 0:
                return errSSLClosedGraceful;
            case ECONNRESET:
                return errSSLClosedAbort;
            case EAGAIN:
                return errSSLWouldBlock;
            default:
                c->lastErr = read;
                return ioErr;
        }
    } else {
        *dataLength = read;
        if (read < requested)
            return errSSLWouldBlock;
        else
            return noErr;
    }
}