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
struct TYPE_4__ {char* path; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int MAX_URL_SIZE ; 
 int ftp_send_command (TYPE_1__*,char*,int const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int ftp_set_dir(FTPContext *s)
{
    static const int cwd_codes[] = {250, 550, 0}; /* 550 is incorrect code */
    char command[MAX_URL_SIZE];

    snprintf(command, sizeof(command), "CWD %s\r\n", s->path);
    if (ftp_send_command(s, command, cwd_codes, NULL) != 250)
        return AVERROR(EIO);
    return 0;
}