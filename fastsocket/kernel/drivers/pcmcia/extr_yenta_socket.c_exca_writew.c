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
typedef  int u16 ;
struct yenta_socket {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*,struct yenta_socket*,unsigned int,int) ; 
 int /*<<< orphan*/  readb (unsigned int) ; 
 int /*<<< orphan*/  writeb (int,unsigned int) ; 

__attribute__((used)) static void exca_writew(struct yenta_socket *socket, unsigned reg, u16 val)
{
	debug("%04x %04x\n", socket, reg, val);
	writeb(val, socket->base + 0x800 + reg);
	writeb(val >> 8, socket->base + 0x800 + reg + 1);

	/* PCI write posting... */
	readb(socket->base + 0x800 + reg);
	readb(socket->base + 0x800 + reg + 1);
}