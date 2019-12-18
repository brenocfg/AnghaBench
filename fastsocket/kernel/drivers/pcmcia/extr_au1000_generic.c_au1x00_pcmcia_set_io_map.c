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
typedef  scalar_t__ u32 ;
struct pcmcia_socket {int dummy; } ;
struct pccard_io_map {size_t map; int flags; unsigned int speed; unsigned int start; scalar_t__ stop; } ;
struct au1000_pcmcia_socket {unsigned int* spd_io; scalar_t__ virt_io; } ;

/* Variables and functions */
 unsigned int AU1000_PCMCIA_IO_SPEED ; 
 int MAP_ACTIVE ; 
 scalar_t__ MAP_SIZE ; 
 size_t MAX_IO_WIN ; 
 int /*<<< orphan*/  debug (char*,size_t) ; 
 struct au1000_pcmcia_socket* to_au1000_socket (struct pcmcia_socket*) ; 

int 
au1x00_pcmcia_set_io_map(struct pcmcia_socket *sock, struct pccard_io_map *map)
{
	struct au1000_pcmcia_socket *skt = to_au1000_socket(sock);
	unsigned int speed;

	if(map->map>=MAX_IO_WIN){
		debug("map (%d) out of range\n", map->map);
		return -1;
	}

	if(map->flags&MAP_ACTIVE){
		speed=(map->speed>0)?map->speed:AU1000_PCMCIA_IO_SPEED;
		skt->spd_io[map->map] = speed;
	}

	map->start=(unsigned int)(u32)skt->virt_io;
	map->stop=map->start+MAP_SIZE;
	return 0;

}