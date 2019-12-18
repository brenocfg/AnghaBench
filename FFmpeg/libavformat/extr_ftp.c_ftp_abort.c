#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int /*<<< orphan*/  conn_control; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ffurl_closep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftp_close_both_connections (TYPE_2__*) ; 
 int /*<<< orphan*/  ftp_close_data_connection (TYPE_2__*) ; 
 int ftp_connect_control_connection (TYPE_1__*) ; 
 scalar_t__ ftp_send_command (TYPE_2__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ftp_status (TYPE_2__*,int /*<<< orphan*/ *,int const*) ; 

__attribute__((used)) static int ftp_abort(URLContext *h)
{
    static const char *command = "ABOR\r\n";
    int err;
    static const int abor_codes[] = {225, 226, 0};
    FTPContext *s = h->priv_data;

    /* According to RCF 959:
       "ABOR command tells the server to abort the previous FTP
       service command and any associated transfer of data."

       There are FTP server implementations that don't response
       to any commands during data transfer in passive mode (including ABOR).

       This implementation closes data connection by force.
    */

    if (ftp_send_command(s, command, NULL, NULL) < 0) {
        ftp_close_both_connections(s);
        if ((err = ftp_connect_control_connection(h)) < 0) {
            av_log(h, AV_LOG_ERROR, "Reconnect failed.\n");
            return err;
        }
    } else {
        ftp_close_data_connection(s);
        if (ftp_status(s, NULL, abor_codes) < 225) {
            /* wu-ftpd also closes control connection after data connection closing */
            ffurl_closep(&s->conn_control);
            if ((err = ftp_connect_control_connection(h)) < 0) {
                av_log(h, AV_LOG_ERROR, "Reconnect failed.\n");
                return err;
            }
        }
    }

    return 0;
}