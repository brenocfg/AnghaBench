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
struct snd_seq_client_port {int dummy; } ;
struct snd_seq_client {int dummy; } ;
struct snd_seq_addr {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (int /*<<< orphan*/ ) ; 
 struct snd_seq_client_port* snd_seq_port_use_ptr (struct snd_seq_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_seq_client_port *get_client_port(struct snd_seq_addr *addr,
						   struct snd_seq_client **cp)
{
	struct snd_seq_client_port *p;
	*cp = snd_seq_client_use_ptr(addr->client);
	if (*cp) {
		p = snd_seq_port_use_ptr(*cp, addr->port);
		if (! p) {
			snd_seq_client_unlock(*cp);
			*cp = NULL;
		}
		return p;
	}
	return NULL;
}