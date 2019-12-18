#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ctl_socket; } ;
struct TYPE_7__ {TYPE_1__ conn; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  rsnd_send_chunk (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsnd_stop_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int rsd_stop(rsound_t *rd)
{
   retro_assert(rd != NULL);
   rsnd_stop_thread(rd);

   const char buf[] = "RSD    5 STOP";

   // Do not really care about errors here.
   // The socket will be closed down in any case in rsnd_reset().
   rsnd_send_chunk(rd->conn.ctl_socket, buf, strlen(buf), 0);

   rsnd_reset(rd);
   return 0;
}