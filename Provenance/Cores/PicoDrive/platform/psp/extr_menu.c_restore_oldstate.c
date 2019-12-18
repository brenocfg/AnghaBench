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
struct TYPE_2__ {int /*<<< orphan*/  video; int /*<<< orphan*/ * vsram; int /*<<< orphan*/ * cram; int /*<<< orphan*/ * vram; } ;

/* Variables and functions */
 TYPE_1__ Pico ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void restore_oldstate(void *ptrx)
{
	unsigned char *ptr = ptrx;
	memcpy(Pico.vram,  ptr,  sizeof(Pico.vram));
	memcpy(Pico.cram,  ptr + sizeof(Pico.vram), sizeof(Pico.cram));
	memcpy(Pico.vsram, ptr + sizeof(Pico.vram) + sizeof(Pico.cram), sizeof(Pico.vsram));
	memcpy(&Pico.video,ptr + sizeof(Pico.vram) + sizeof(Pico.cram) + sizeof(Pico.vsram), sizeof(Pico.video));
	free(ptrx);
}