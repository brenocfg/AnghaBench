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

int connection_consume_verify_login(struct connection *conn)
{
    int prompt_ending = util_memsearch(conn->rdbuf, conn->rdbuf_pos, TOKEN_RESPONSE, strlen(TOKEN_RESPONSE));

    if (prompt_ending == -1)
        return 0;
    else
        return prompt_ending;
}