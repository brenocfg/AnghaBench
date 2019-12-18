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
struct TYPE_3__ {int base; } ;
typedef  TYPE_1__ vrc4173_socket_t ;
typedef  int uint16_t ;
typedef  int u16 ;

/* Variables and functions */
 int EXCA_REGS_BASE ; 
 int readb (int) ; 

__attribute__((used)) static inline uint16_t exca_readw(vrc4173_socket_t *socket, uint16_t offset)
{
	uint16_t val;

	val = readb(socket->base + EXCA_REGS_BASE + offset);
	val |= (u16)readb(socket->base + EXCA_REGS_BASE + offset + 1) << 8;

	return val;
}