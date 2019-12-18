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
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
#define  GNUTLS_E_AGAIN 131 
#define  GNUTLS_E_INTERRUPTED 130 
#define  GNUTLS_E_PREMATURE_TERMINATION 129 
#define  GNUTLS_E_WARNING_ALERT_RECEIVED 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 

__attribute__((used)) static int print_tls_error(URLContext *h, int ret)
{
    switch (ret) {
    case GNUTLS_E_AGAIN:
        return AVERROR(EAGAIN);
    case GNUTLS_E_INTERRUPTED:
#ifdef GNUTLS_E_PREMATURE_TERMINATION
    case GNUTLS_E_PREMATURE_TERMINATION:
#endif
        break;
    case GNUTLS_E_WARNING_ALERT_RECEIVED:
        av_log(h, AV_LOG_WARNING, "%s\n", gnutls_strerror(ret));
        break;
    default:
        av_log(h, AV_LOG_ERROR, "%s\n", gnutls_strerror(ret));
        break;
    }
    return AVERROR(EIO);
}