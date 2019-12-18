#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int addr; char* user; char* pass; char* arch; int /*<<< orphan*/  port; } ;
struct TYPE_4__ {scalar_t__ deadline; int /*<<< orphan*/  data; } ;
struct connection {int fd; int state_telnet; int /*<<< orphan*/  lock; TYPE_3__* srv; TYPE_2__ info; scalar_t__ success; scalar_t__ rdbuf_pos; int /*<<< orphan*/  rdbuf; void* ctrlc_retry; void* retry_bin; void* open; scalar_t__ last_recv; TYPE_1__ output_buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  curr_open; int /*<<< orphan*/  total_failures; int /*<<< orphan*/  total_successes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_DEC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ATOMIC_INC (int /*<<< orphan*/ *) ; 
 void* FALSE ; 
 int TELNET_CLOSED ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void connection_close(struct connection *conn)
{
    pthread_mutex_lock(&conn->lock);

    if (conn->open)
    {
#ifdef DEBUG
        printf("[FD%d] Shut down connection\n", conn->fd);
#endif
        memset(conn->output_buffer.data, 0, sizeof(conn->output_buffer.data));
        conn->output_buffer.deadline = 0;
        conn->last_recv = 0;
        conn->open = FALSE;
        conn->retry_bin = FALSE;
        conn->ctrlc_retry = FALSE;
        memset(conn->rdbuf, 0, sizeof(conn->rdbuf));
        conn->rdbuf_pos = 0;

        if (conn->srv == NULL)
        {
            printf("srv == NULL\n");
            return;
        }

        if (conn->success)
        {
            ATOMIC_INC(&conn->srv->total_successes);
            fprintf(stderr, "OK|%d.%d.%d.%d:%d %s:%s %s\n",
                conn->info.addr & 0xff, (conn->info.addr >> 8) & 0xff, (conn->info.addr >> 16) & 0xff, (conn->info.addr >> 24) & 0xff,
                ntohs(conn->info.port),
                conn->info.user, conn->info.pass, conn->info.arch);
        }
        else
        {
            ATOMIC_INC(&conn->srv->total_failures);
            fprintf(stderr, "ERR|%d.%d.%d.%d:%d %s:%s %s|%d\n",
                conn->info.addr & 0xff, (conn->info.addr >> 8) & 0xff, (conn->info.addr >> 16) & 0xff, (conn->info.addr >> 24) & 0xff,
                ntohs(conn->info.port),
                conn->info.user, conn->info.pass, conn->info.arch,
                conn->state_telnet);
        }
    }
    conn->state_telnet = TELNET_CLOSED;

    if (conn->fd != -1)
    {
        close(conn->fd);
        conn->fd = -1;
        ATOMIC_DEC(&conn->srv->curr_open);
    }

    pthread_mutex_unlock(&conn->lock);
}