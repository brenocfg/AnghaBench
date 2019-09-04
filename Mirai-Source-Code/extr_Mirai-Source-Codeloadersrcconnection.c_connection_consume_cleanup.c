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
struct connection {int /*<<< orphan*/  rdbuf_pos; int /*<<< orphan*/  rdbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_RESPONSE ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int util_memsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int connection_consume_cleanup(struct connection *conn)
{
    int offset = util_memsearch(conn->rdbuf, conn->rdbuf_pos, TOKEN_RESPONSE, strlen(TOKEN_RESPONSE));

    if (offset == -1)
        return 0;
    return offset;
}