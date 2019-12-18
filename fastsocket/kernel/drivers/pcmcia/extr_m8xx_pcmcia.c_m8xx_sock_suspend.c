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
struct pcmcia_socket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dead_socket ; 
 int m8xx_set_socket (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m8xx_sock_suspend(struct pcmcia_socket *sock)
{
	return m8xx_set_socket(sock, &dead_socket);
}