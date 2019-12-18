#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct au1000_pcmcia_socket {int dummy; } ;
struct TYPE_2__ {scalar_t__ pcmcia; } ;

/* Variables and functions */
 int /*<<< orphan*/  au_sync_delay (int) ; 
 TYPE_1__* bcsr ; 

__attribute__((used)) static void db1x00_pcmcia_shutdown(struct au1000_pcmcia_socket *skt)
{
	bcsr->pcmcia = 0; /* turn off power */
	au_sync_delay(2);
}