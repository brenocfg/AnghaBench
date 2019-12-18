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

/* Variables and functions */
 int JOB_DATA_SIZE_LIMIT_MAX ; 
 int SERVER () ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int job_data_size_limit ; 
 int /*<<< orphan*/  memset (char*,char,int const) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 

void
cttest_job_size_max_plus_1()
{
    /* verify that server reject the job larger than maximum allowed. */
    job_data_size_limit = JOB_DATA_SIZE_LIMIT_MAX;
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 0 1073741825\r\n");

    const int len = 1024*1024;
    char body[len+1];
    memset(body, 'a', len);
    body[len] = 0;

    int i;
    for (i=0; i<JOB_DATA_SIZE_LIMIT_MAX; i+=len) {
        mustsend(fd, body);
    }
    mustsend(fd, "x");
    mustsend(fd, "\r\n");
    ckresp(fd, "JOB_TOO_BIG\r\n");
}