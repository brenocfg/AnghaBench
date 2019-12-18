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
typedef  int ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  totlen; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ clusterMsg ;
struct TYPE_6__ {scalar_t__ rcvbuf; } ;
typedef  TYPE_2__ clusterLink ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  aeEventLoop ;

/* Variables and functions */
 unsigned int CLUSTERMSG_MIN_LEN ; 
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 scalar_t__ clusterProcessPacket (TYPE_2__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  handleLinkIOError (TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 int read (int,char*,unsigned int) ; 
 scalar_t__ sdscatlen (scalar_t__,char*,int) ; 
 scalar_t__ sdsempty () ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 unsigned int sdslen (scalar_t__) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 char* strerror (scalar_t__) ; 

void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    char buf[sizeof(clusterMsg)];
    ssize_t nread;
    clusterMsg *hdr;
    clusterLink *link = (clusterLink*) privdata;
    unsigned int readlen, rcvbuflen;
    UNUSED(el);
    UNUSED(mask);

    while(1) { /* Read as long as there is data to read. */
        rcvbuflen = sdslen(link->rcvbuf);
        if (rcvbuflen < 8) {
            /* First, obtain the first 8 bytes to get the full message
             * length. */
            readlen = 8 - rcvbuflen;
        } else {
            /* Finally read the full message. */
            hdr = (clusterMsg*) link->rcvbuf;
            if (rcvbuflen == 8) {
                /* Perform some sanity check on the message signature
                 * and length. */
                if (memcmp(hdr->sig,"DbuZ",4) != 0 ||
                    ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN)
                {
                    serverLog(LL_WARNING,
                        "Bad message length or signature received "
                        "from Cluster bus.");
                    handleLinkIOError(link);
                    return;
                }
            }
            readlen = ntohl(hdr->totlen) - rcvbuflen;
            if (readlen > sizeof(buf)) readlen = sizeof(buf);
        }

        nread = read(fd,buf,readlen);
        if (nread == -1 && errno == EAGAIN) return; /* No more data ready. */

        if (nread <= 0) {
            /* I/O error... */
            serverLog(LL_DEBUG,"I/O error reading from node link: %s",
                (nread == 0) ? "connection closed" : strerror(errno));
            handleLinkIOError(link);
            return;
        } else {
            /* Read data and recast the pointer to the new buffer. */
            link->rcvbuf = sdscatlen(link->rcvbuf,buf,nread);
            hdr = (clusterMsg*) link->rcvbuf;
            rcvbuflen += nread;
        }

        /* Total length obtained? Process this packet. */
        if (rcvbuflen >= 8 && rcvbuflen == ntohl(hdr->totlen)) {
            if (clusterProcessPacket(link)) {
                sdsfree(link->rcvbuf);
                link->rcvbuf = sdsempty();
            } else {
                return; /* Link no longer valid. */
            }
        }
    }
}