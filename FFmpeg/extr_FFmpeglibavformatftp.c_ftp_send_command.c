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
struct TYPE_5__ {int /*<<< orphan*/  conn_control; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*,char const*) ; 
 int ffurl_write (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int ftp_status (TYPE_1__*,char**,int const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int ftp_send_command(FTPContext *s, const char *command,
                            const int response_codes[], char **response)
{
    int err;

    ff_dlog(s, "%s", command);

    if (response)
        *response = NULL;

    if (!s->conn_control)
        return AVERROR(EIO);

    if ((err = ffurl_write(s->conn_control, command, strlen(command))) < 0)
        return err;
    if (!err)
        return -1;

    /* return status */
    if (response_codes) {
        return ftp_status(s, response, response_codes);
    }
    return 0;
}