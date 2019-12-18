#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_socket {int dummy; } ;
struct TYPE_5__ {int map; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ pccard_mem_map ;
struct TYPE_6__ {int member_4; int map; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ pccard_io_map ;

/* Variables and functions */
 int PCMCIA_IO_WIN_NO ; 
 int PCMCIA_MEM_WIN_NO ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m8xx_set_io_map (struct pcmcia_socket*,TYPE_2__*) ; 
 int /*<<< orphan*/  m8xx_set_mem_map (struct pcmcia_socket*,TYPE_1__*) ; 
 int /*<<< orphan*/  m8xx_set_socket (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s ; 

__attribute__((used)) static int m8xx_sock_init(struct pcmcia_socket *sock)
{
	int i;
	pccard_io_map io = { 0, 0, 0, 0, 1 };
	pccard_mem_map mem = { 0, 0, 0, 0, 0, 0 };

	dprintk("sock_init(%d)\n", s);

	m8xx_set_socket(sock, &dead_socket);
	for (i = 0; i < PCMCIA_IO_WIN_NO; i++) {
		io.map = i;
		m8xx_set_io_map(sock, &io);
	}
	for (i = 0; i < PCMCIA_MEM_WIN_NO; i++) {
		mem.map = i;
		m8xx_set_mem_map(sock, &mem);
	}

	return 0;

}