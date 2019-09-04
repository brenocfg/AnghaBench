#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  message ;
typedef  enum RTSPStatusCode { ____Placeholder_RTSPStatusCode } RTSPStatusCode ;
struct TYPE_8__ {int code; char* message; } ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  rtsp_hd_out; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LIBAVFORMAT_IDENT ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  av_strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffurl_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 TYPE_3__* status_messages ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int rtsp_send_reply(AVFormatContext *s, enum RTSPStatusCode code,
                           const char *extracontent, uint16_t seq)
{
    RTSPState *rt = s->priv_data;
    char message[4096];
    int index = 0;
    while (status_messages[index].code) {
        if (status_messages[index].code == code) {
            snprintf(message, sizeof(message), "RTSP/1.0 %d %s\r\n",
                     code, status_messages[index].message);
            break;
        }
        index++;
    }
    if (!status_messages[index].code)
        return AVERROR(EINVAL);
    av_strlcatf(message, sizeof(message), "CSeq: %d\r\n", seq);
    av_strlcatf(message, sizeof(message), "Server: %s\r\n", LIBAVFORMAT_IDENT);
    if (extracontent)
        av_strlcat(message, extracontent, sizeof(message));
    av_strlcat(message, "\r\n", sizeof(message));
    av_log(s, AV_LOG_TRACE, "Sending response:\n%s", message);
    ffurl_write(rt->rtsp_hd_out, message, strlen(message));

    return 0;
}