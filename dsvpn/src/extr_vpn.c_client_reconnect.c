#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ is_server; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 unsigned int RECONNECT_ATTEMPTS ; 
 scalar_t__ client_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  client_disconnect (TYPE_1__*) ; 
 scalar_t__ exit_signal_received ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static int client_reconnect(Context *context)
{
    unsigned int i;

    client_disconnect(context);
    if (context->is_server) {
        return 0;
    }
    for (i = 0; exit_signal_received == 0 && i < RECONNECT_ATTEMPTS; i++) {
        puts("Trying to reconnect");
        sleep(i > 3 ? 3 : i);
        if (client_connect(context) == 0) {
            return 0;
        }
    }
    return -1;
}