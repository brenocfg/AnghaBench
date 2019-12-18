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
struct TYPE_4__ {char* path; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int CONTROL_BUFFER_SIZE ; 
 int /*<<< orphan*/  DOWNLOADING ; 
 int /*<<< orphan*/  EIO ; 
 int ftp_send_command (TYPE_1__*,char*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int ftp_retrieve(FTPContext *s)
{
    char command[CONTROL_BUFFER_SIZE];
    static const int retr_codes[] = {150, 125, 0};
    int resp_code;

    snprintf(command, sizeof(command), "RETR %s\r\n", s->path);
    resp_code = ftp_send_command(s, command, retr_codes, NULL);
    if (resp_code != 125 && resp_code != 150)
        return AVERROR(EIO);

    s->state = DOWNLOADING;

    return 0;
}