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
typedef  int /*<<< orphan*/  vrc4173_socket_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int u_char ;
struct pccard_mem_map {int map; int card_start; int sys_start; int sys_stop; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADR_WIN_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAP_16BIT ; 
 int /*<<< orphan*/  MAP_ACTIVE ; 
 int /*<<< orphan*/  MAP_ATTRIB ; 
 int /*<<< orphan*/  MAP_WRPROT ; 
 int MEM_WIN_DSIZE ; 
 int /*<<< orphan*/  MEM_WIN_EA (int) ; 
 int MEM_WIN_EN (int) ; 
 int /*<<< orphan*/  MEM_WIN_OA (int) ; 
 int MEM_WIN_REGSET ; 
 int /*<<< orphan*/  MEM_WIN_SA (int) ; 
 int /*<<< orphan*/  MEM_WIN_SAU (int) ; 
 int MEM_WIN_WP ; 
 int /*<<< orphan*/ * cardu_sockets ; 
 int exca_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int exca_readw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cardu_get_mem_map(unsigned int sock, struct pccard_mem_map *mem)
{
	vrc4173_socket_t *socket = &cardu_sockets[sock];
	uint32_t start, stop, offset, page;
	uint8_t window;
	u_char map;

	map = mem->map;
	if (map > 4)
		return -EINVAL;

	window = exca_readb(socket, ADR_WIN_EN);
	mem->flags = (window & MEM_WIN_EN(map)) ? MAP_ACTIVE : 0;

	start = exca_readw(socket, MEM_WIN_SA(map));
	mem->flags |= (start & MEM_WIN_DSIZE) ? MAP_16BIT : 0;
	start = (start & 0x0fff) << 12;

	stop = exca_readw(socket, MEM_WIN_EA(map));
	stop = ((stop & 0x0fff) << 12) + 0x0fff;

	offset = exca_readw(socket, MEM_WIN_OA(map));
	mem->flags |= (offset & MEM_WIN_WP) ? MAP_WRPROT : 0;
	mem->flags |= (offset & MEM_WIN_REGSET) ? MAP_ATTRIB : 0;
	offset = ((offset & 0x3fff) << 12) + start;
	mem->card_start = offset & 0x03ffffff;

	page = exca_readb(socket, MEM_WIN_SAU(map)) << 24;
	mem->sys_start = start + page;
	mem->sys_stop = start + page;

	return 0;
}