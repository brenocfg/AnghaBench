#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int server_data_port; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*,int) ; 
 int ftp_send_command (TYPE_1__*,char const*,int const*,char**) ; 

__attribute__((used)) static int ftp_passive_mode(FTPContext *s)
{
    char *res = NULL, *start = NULL, *end = NULL;
    int i;
    static const char *command = "PASV\r\n";
    static const int pasv_codes[] = {227, 0};

    if (ftp_send_command(s, command, pasv_codes, &res) != 227 || !res)
        goto fail;

    for (i = 0; res[i]; ++i) {
        if (res[i] == '(') {
            start = res + i + 1;
        } else if (res[i] == ')') {
            end = res + i;
            break;
        }
    }
    if (!start || !end)
        goto fail;

    *end  = '\0';
    /* skip ip */
    if (!av_strtok(start, ",", &end)) goto fail;
    if (!av_strtok(end, ",", &end)) goto fail;
    if (!av_strtok(end, ",", &end)) goto fail;
    if (!av_strtok(end, ",", &end)) goto fail;

    /* parse port number */
    start = av_strtok(end, ",", &end);
    if (!start) goto fail;
    s->server_data_port = atoi(start) * 256;
    start = av_strtok(end, ",", &end);
    if (!start) goto fail;
    s->server_data_port += atoi(start);
    ff_dlog(s, "Server data port: %d\n", s->server_data_port);

    av_free(res);
    return 0;

  fail:
    av_free(res);
    s->server_data_port = -1;
    return AVERROR(EIO);
}