#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_1__ hb_net_t ;

/* Variables and functions */
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int hb_net_recv( hb_net_t * n, char * buffer, int size )
{
    return recv( n->socket, buffer, size - 1, 0 );
}