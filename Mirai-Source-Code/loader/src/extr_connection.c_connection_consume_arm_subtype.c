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
struct TYPE_2__ {int /*<<< orphan*/  arch; } ;
struct connection {int rdbuf_pos; int fd; TYPE_1__ info; int /*<<< orphan*/  rdbuf; } ;

/* Variables and functions */
 char* TOKEN_RESPONSE ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 
 int util_memsearch (int /*<<< orphan*/ ,int,char*,int) ; 

int connection_consume_arm_subtype(struct connection *conn)
{
    int offset = util_memsearch(conn->rdbuf, conn->rdbuf_pos, TOKEN_RESPONSE, strlen(TOKEN_RESPONSE));

    if (offset == -1)
        return 0;

    if (util_memsearch(conn->rdbuf, offset, "ARMv7", 5) != -1 || util_memsearch(conn->rdbuf, offset, "ARMv6", 5) != -1)
    {
#ifdef DEBUG
        printf("[FD%d] Arch has ARMv7!\n", conn->fd);
#endif
        strcpy(conn->info.arch, "arm7");
    }

    return offset;
}