#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rbuf ;
struct TYPE_15__ {TYPE_1__* priv_data; } ;
struct TYPE_14__ {scalar_t__ seq; } ;
struct TYPE_13__ {scalar_t__ seq; scalar_t__* session_id; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ RTSPMessageHeader ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int check_sessionid (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_rtsp_parse_line (TYPE_3__*,TYPE_2__*,char*,TYPE_1__*,char const*) ; 
 int read_line (TYPE_3__*,char*,int,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static inline int rtsp_read_request(AVFormatContext *s,
                                    RTSPMessageHeader *request,
                                    const char *method)
{
    RTSPState *rt = s->priv_data;
    char rbuf[1024];
    int rbuflen, ret;
    do {
        ret = read_line(s, rbuf, sizeof(rbuf), &rbuflen);
        if (ret)
            return ret;
        if (rbuflen > 1) {
            av_log(s, AV_LOG_TRACE, "Parsing[%d]: %s\n", rbuflen, rbuf);
            ff_rtsp_parse_line(s, request, rbuf, rt, method);
        }
    } while (rbuflen > 0);
    if (request->seq != rt->seq + 1) {
        av_log(s, AV_LOG_ERROR, "Unexpected Sequence number %d\n",
               request->seq);
        return AVERROR(EINVAL);
    }
    if (rt->session_id[0] && strcmp(method, "OPTIONS")) {
        ret = check_sessionid(s, request);
        if (ret)
            return ret;
    }

    return 0;
}