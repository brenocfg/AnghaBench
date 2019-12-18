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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FTPContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BPRINT_SIZE_AUTOMATIC ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int CONTROL_BUFFER_SIZE ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int ftp_get_line (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int ftp_status(FTPContext *s, char **line, const int response_codes[])
{
    int err, i, dash = 0, result = 0, code_found = 0, linesize;
    char buf[CONTROL_BUFFER_SIZE];
    AVBPrint line_buffer;

    if (line)
        av_bprint_init(&line_buffer, 0, AV_BPRINT_SIZE_AUTOMATIC);

    while (!code_found || dash) {
        if ((err = ftp_get_line(s, buf, sizeof(buf))) < 0) {
            if (line)
                av_bprint_finalize(&line_buffer, NULL);
            return err;
        }

        av_log(s, AV_LOG_DEBUG, "%s\n", buf);

        linesize = strlen(buf);
        err = 0;
        if (linesize >= 3) {
            for (i = 0; i < 3; ++i) {
                if (buf[i] < '0' || buf[i] > '9') {
                    err = 0;
                    break;
                }
                err *= 10;
                err += buf[i] - '0';
            }
        }

        if (!code_found) {
            if (err >= 500) {
                code_found = 1;
                result = err;
            } else
                for (i = 0; response_codes[i]; ++i) {
                    if (err == response_codes[i]) {
                        code_found = 1;
                        result = err;
                        break;
                    }
                }
        }
        if (code_found) {
            if (line)
                av_bprintf(&line_buffer, "%s\r\n", buf);
            if (linesize >= 4) {
                if (!dash && buf[3] == '-')
                    dash = err;
                else if (err == dash && buf[3] == ' ')
                    dash = 0;
            }
        }
    }

    if (line)
        av_bprint_finalize(&line_buffer, line);
    return result;
}