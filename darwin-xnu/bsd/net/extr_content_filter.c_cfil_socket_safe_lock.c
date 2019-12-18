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
struct inpcb {int /*<<< orphan*/  inp_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  WNT_ACQUIRE ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 scalar_t__ WNT_STOPUSING ; 
 scalar_t__ in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  socket_unlock (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
cfil_socket_safe_lock(struct inpcb *inp)
{
    if (in_pcb_checkstate(inp, WNT_ACQUIRE, 0) != WNT_STOPUSING) {
        socket_lock(inp->inp_socket, 1);
        if (in_pcb_checkstate(inp, WNT_RELEASE, 1) != WNT_STOPUSING) {
            return true;
        }
        socket_unlock(inp->inp_socket, 1);
    }
    return false;
}