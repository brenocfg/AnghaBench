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
struct snd_seq_event {int type; } ;

/* Variables and functions */
 scalar_t__ setheader (struct snd_seq_event*,int,int) ; 
 int /*<<< orphan*/  snd_seq_kernel_client_dispatch (int /*<<< orphan*/ ,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysclient ; 

void snd_seq_system_broadcast(int client, int port, int type)
{
	struct snd_seq_event ev;
	
	if (setheader(&ev, client, port) < 0)
		return;
	ev.type = type;
	snd_seq_kernel_client_dispatch(sysclient, &ev, 0, 0);
}