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
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int SRT_EASYNCRCV ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int srt_getlasterror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srt_getlasterror_str () ; 

__attribute__((used)) static int libsrt_neterrno(URLContext *h)
{
    int err = srt_getlasterror(NULL);
    av_log(h, AV_LOG_ERROR, "%s\n", srt_getlasterror_str());
    if (err == SRT_EASYNCRCV)
        return AVERROR(EAGAIN);
    return AVERROR_UNKNOWN;
}