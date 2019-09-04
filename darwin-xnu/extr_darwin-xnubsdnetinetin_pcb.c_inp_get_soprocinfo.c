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
struct socket {scalar_t__ last_pid; int so_flags; scalar_t__ e_pid; int /*<<< orphan*/  e_uuid; int /*<<< orphan*/  last_uuid; } ;
struct so_procinfo {scalar_t__ spi_pid; int spi_delegated; scalar_t__ spi_epid; int /*<<< orphan*/  spi_euuid; int /*<<< orphan*/  spi_uuid; } ;
struct inpcb {struct socket* inp_socket; } ;

/* Variables and functions */
 int SOF_DELEGATED ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
inp_get_soprocinfo(struct inpcb *inp, struct so_procinfo *soprocinfo)
{
	struct socket *so = inp->inp_socket;

	soprocinfo->spi_pid = so->last_pid;
	if (so->last_pid != 0)
		uuid_copy(soprocinfo->spi_uuid, so->last_uuid);
	/*
	 * When not delegated, the effective pid is the same as the real pid
	 */
	if (so->so_flags & SOF_DELEGATED) {
		soprocinfo->spi_delegated = 1;
		soprocinfo->spi_epid = so->e_pid;
		uuid_copy(soprocinfo->spi_euuid, so->e_uuid);
	} else {
		soprocinfo->spi_delegated = 0;
		soprocinfo->spi_epid = so->last_pid;
	}
}