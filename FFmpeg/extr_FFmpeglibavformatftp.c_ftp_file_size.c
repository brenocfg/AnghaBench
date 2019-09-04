#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  command ;
struct TYPE_4__ {char* path; int filesize; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CONTROL_BUFFER_SIZE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int ftp_send_command (TYPE_1__*,char*,int const*,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int strlen (char*) ; 
 int strtoll (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ftp_file_size(FTPContext *s)
{
    char command[CONTROL_BUFFER_SIZE];
    char *res = NULL;
    static const int size_codes[] = {213, 0};

    snprintf(command, sizeof(command), "SIZE %s\r\n", s->path);
    if (ftp_send_command(s, command, size_codes, &res) == 213 && res && strlen(res) > 4) {
        s->filesize = strtoll(&res[4], NULL, 10);
    } else {
        s->filesize = -1;
        av_free(res);
        return AVERROR(EIO);
    }

    av_free(res);
    return 0;
}