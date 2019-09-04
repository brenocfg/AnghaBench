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
typedef  int /*<<< orphan*/  URLProtocol ;
typedef  int /*<<< orphan*/  URLContext ;
typedef  int /*<<< orphan*/  AVIOInterruptCB ;

/* Variables and functions */
 int AVERROR_PROTOCOL_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 int url_alloc_for_protocol (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * url_find_protocol (char const*) ; 

int ffurl_alloc(URLContext **puc, const char *filename, int flags,
                const AVIOInterruptCB *int_cb)
{
    const URLProtocol *p = NULL;

    p = url_find_protocol(filename);
    if (p)
       return url_alloc_for_protocol(puc, p, filename, flags, int_cb);

    *puc = NULL;
    if (av_strstart(filename, "https:", NULL) || av_strstart(filename, "tls:", NULL))
        av_log(NULL, AV_LOG_WARNING, "https protocol not found, recompile FFmpeg with "
                                     "openssl, gnutls "
                                     "or securetransport enabled.\n");
    return AVERROR_PROTOCOL_NOT_FOUND;
}