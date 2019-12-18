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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  host ;
typedef  enum RTSPMethod { ____Placeholder_RTSPMethod } RTSPMethod ;
typedef  int /*<<< orphan*/  ctl_path ;
typedef  int /*<<< orphan*/  ctl_host ;
typedef  int /*<<< orphan*/  ctl_auth ;
typedef  int /*<<< orphan*/  auth ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {char* control_uri; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ RTSPState ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ANNOUNCE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PROTOCOL_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EIO ; 
 int OPTIONS ; 
 int PAUSE ; 
 int RECORD ; 
 int /*<<< orphan*/  RTSP_STATE_IDLE ; 
 int /*<<< orphan*/  RTSP_STATE_PAUSED ; 
 int /*<<< orphan*/  RTSP_STATE_STREAMING ; 
 int SETUP ; 
 int TEARDOWN ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,int*,char*,int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static inline int parse_command_line(AVFormatContext *s, const char *line,
                                     int linelen, char *uri, int urisize,
                                     char *method, int methodsize,
                                     enum RTSPMethod *methodcode)
{
    RTSPState *rt = s->priv_data;
    const char *linept, *searchlinept;
    linept = strchr(line, ' ');

    if (!linept) {
        av_log(s, AV_LOG_ERROR, "Error parsing method string\n");
        return AVERROR_INVALIDDATA;
    }

    if (linept - line > methodsize - 1) {
        av_log(s, AV_LOG_ERROR, "Method string too long\n");
        return AVERROR(EIO);
    }
    memcpy(method, line, linept - line);
    method[linept - line] = '\0';
    linept++;
    if (!strcmp(method, "ANNOUNCE"))
        *methodcode = ANNOUNCE;
    else if (!strcmp(method, "OPTIONS"))
        *methodcode = OPTIONS;
    else if (!strcmp(method, "RECORD"))
        *methodcode = RECORD;
    else if (!strcmp(method, "SETUP"))
        *methodcode = SETUP;
    else if (!strcmp(method, "PAUSE"))
        *methodcode = PAUSE;
    else if (!strcmp(method, "TEARDOWN"))
        *methodcode = TEARDOWN;
    else
        *methodcode = UNKNOWN;
    /* Check method with the state  */
    if (rt->state == RTSP_STATE_IDLE) {
        if ((*methodcode != ANNOUNCE) && (*methodcode != OPTIONS)) {
            av_log(s, AV_LOG_ERROR, "Unexpected command in Idle State %s\n",
                   line);
            return AVERROR_PROTOCOL_NOT_FOUND;
        }
    } else if (rt->state == RTSP_STATE_PAUSED) {
        if ((*methodcode != OPTIONS) && (*methodcode != RECORD)
            && (*methodcode != SETUP)) {
            av_log(s, AV_LOG_ERROR, "Unexpected command in Paused State %s\n",
                   line);
            return AVERROR_PROTOCOL_NOT_FOUND;
        }
    } else if (rt->state == RTSP_STATE_STREAMING) {
        if ((*methodcode != PAUSE) && (*methodcode != OPTIONS)
            && (*methodcode != TEARDOWN)) {
            av_log(s, AV_LOG_ERROR, "Unexpected command in Streaming State"
                   " %s\n", line);
            return AVERROR_PROTOCOL_NOT_FOUND;
        }
    } else {
        av_log(s, AV_LOG_ERROR, "Unexpected State [%d]\n", rt->state);
        return AVERROR_BUG;
    }

    searchlinept = strchr(linept, ' ');
    if (!searchlinept) {
        av_log(s, AV_LOG_ERROR, "Error parsing message URI\n");
        return AVERROR_INVALIDDATA;
    }
    if (searchlinept - linept > urisize - 1) {
        av_log(s, AV_LOG_ERROR, "uri string length exceeded buffer size\n");
        return AVERROR(EIO);
    }
    memcpy(uri, linept, searchlinept - linept);
    uri[searchlinept - linept] = '\0';
    if (strcmp(rt->control_uri, uri)) {
        char host[128], path[512], auth[128];
        int port;
        char ctl_host[128], ctl_path[512], ctl_auth[128];
        int ctl_port;
        av_url_split(NULL, 0, auth, sizeof(auth), host, sizeof(host), &port,
                     path, sizeof(path), uri);
        av_url_split(NULL, 0, ctl_auth, sizeof(ctl_auth), ctl_host,
                     sizeof(ctl_host), &ctl_port, ctl_path, sizeof(ctl_path),
                     rt->control_uri);
        if (strcmp(host, ctl_host))
            av_log(s, AV_LOG_INFO, "Host %s differs from expected %s\n",
                   host, ctl_host);
        if (strcmp(path, ctl_path) && *methodcode != SETUP)
            av_log(s, AV_LOG_WARNING, "WARNING: Path %s differs from expected"
                   " %s\n", path, ctl_path);
        if (*methodcode == ANNOUNCE) {
            av_log(s, AV_LOG_INFO,
                   "Updating control URI to %s\n", uri);
            av_strlcpy(rt->control_uri, uri, sizeof(rt->control_uri));
        }
    }

    linept = searchlinept + 1;
    if (!av_strstart(linept, "RTSP/1.0", NULL)) {
        av_log(s, AV_LOG_ERROR, "Error parsing protocol or version\n");
        return AVERROR_PROTOCOL_NOT_FOUND;
    }
    return 0;
}