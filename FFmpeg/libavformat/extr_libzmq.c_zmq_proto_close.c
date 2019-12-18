#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ ZMQContext ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
typedef  TYPE_2__ URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  zmq_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmq_ctx_term (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zmq_proto_close(URLContext *h)
{
    ZMQContext *s = h->priv_data;
    zmq_close(s->socket);
    zmq_ctx_term(s->context);
    return 0;
}