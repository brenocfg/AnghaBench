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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Conn ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  STATE_CLOSE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  twarn (char*,char const*) ; 

__attribute__((used)) static void
check_err(Conn *c, const char *s)
{
    if (errno == EAGAIN)
        return;
    if (errno == EINTR)
        return;
    if (errno == EWOULDBLOCK)
        return;

    twarn("%s", s);
    c->state = STATE_CLOSE;
}