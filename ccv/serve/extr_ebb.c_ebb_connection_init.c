#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  new_request; TYPE_1__* data; } ;
struct TYPE_6__ {int fd; int /*<<< orphan*/ * data; int /*<<< orphan*/ * on_close; int /*<<< orphan*/ * on_timeout; int /*<<< orphan*/ * new_request; int /*<<< orphan*/ * new_buf; TYPE_2__ timeout_watcher; TYPE_2__ goodbye_watcher; TYPE_3__ read_watcher; int /*<<< orphan*/ * to_write; TYPE_3__ write_watcher; TYPE_4__ parser; scalar_t__ open; int /*<<< orphan*/ * ip; int /*<<< orphan*/ * server; } ;
typedef  TYPE_1__ ebb_connection ;

/* Variables and functions */
 int EBB_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  ebb_request_parser_init (TYPE_4__*) ; 
 int /*<<< orphan*/  ev_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_timer_init (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  new_request_wrapper ; 
 int /*<<< orphan*/  on_goodbye ; 
 int /*<<< orphan*/  on_readable ; 
 int /*<<< orphan*/  on_timeout ; 
 int /*<<< orphan*/  on_writable ; 

void 
ebb_connection_init(ebb_connection *connection)
{
  connection->fd = -1;
  connection->server = NULL;
  connection->ip = NULL;
  connection->open = 0;

  ebb_request_parser_init( &connection->parser );
  connection->parser.data = connection;
  connection->parser.new_request = new_request_wrapper;
  
  ev_init (&connection->write_watcher, on_writable);
  connection->write_watcher.data = connection;
  connection->to_write = NULL;

  ev_init(&connection->read_watcher, on_readable);
  connection->read_watcher.data = connection;

  ev_timer_init(&connection->goodbye_watcher, on_goodbye, 0., 0.);
  connection->goodbye_watcher.data = connection;  

  ev_timer_init(&connection->timeout_watcher, on_timeout, EBB_DEFAULT_TIMEOUT, 0.);
  connection->timeout_watcher.data = connection;  

  connection->new_buf = NULL;
  connection->new_request = NULL;
  connection->on_timeout = NULL;
  connection->on_close = NULL;
  connection->data = NULL;
}