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
struct connection {int rdbuf_pos; char* rdbuf; } ;

/* Variables and functions */

int connection_consume_prompt(struct connection *conn)
{
    char *pch;
    int i, prompt_ending = -1;

    for (i = conn->rdbuf_pos; i >= 0; i--)
    {
        if (conn->rdbuf[i] == ':' || conn->rdbuf[i] == '>' || conn->rdbuf[i] == '$' || conn->rdbuf[i] == '#' || conn->rdbuf[i] == '%')
        {
#ifdef DEBUG
            printf("matched any prompt at %d, \"%c\", \"%s\"\n", i, conn->rdbuf[i], conn->rdbuf);
#endif
            prompt_ending = i;
            break;
        }
    }

    if (prompt_ending == -1)
        return 0;
    else
        return prompt_ending;
}