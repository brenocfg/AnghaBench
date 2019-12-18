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
struct telnet_info {int dummy; } ;
struct server {scalar_t__ max_open; int /*<<< orphan*/  curr_open; } ;

/* Variables and functions */
 scalar_t__ ATOMIC_GET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATOMIC_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  server_telnet_probe (struct server*,struct telnet_info*) ; 
 int /*<<< orphan*/  sleep (int) ; 

void server_queue_telnet(struct server *srv, struct telnet_info *info)
{
    while (ATOMIC_GET(&srv->curr_open) >= srv->max_open)
    {
        sleep(1);
    }
    ATOMIC_INC(&srv->curr_open);

    if (srv == NULL)
        printf("srv == NULL 3\n");

    server_telnet_probe(srv, info);
}