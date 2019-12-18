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
typedef  int /*<<< orphan*/  pointer ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetFetch ) (int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  C68K ; 
 int /*<<< orphan*/  C68k_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* M68K ; 
 int /*<<< orphan*/ * SoundDummy ; 
 int /*<<< orphan*/ * T2MemoryInit (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int M68KC68KInit(void) {
	int i;

	// Setup a 64k buffer filled with invalid 68k instructions to serve
	// as a default map
	if ((SoundDummy = T2MemoryInit(0x10000)) != NULL)
		memset(SoundDummy, 0xFF, 0x10000);

	C68k_Init(&C68K, NULL); // not sure if I need the int callback or not

	for (i = 0x10; i < 0x100; i++)
		M68K->SetFetch(i << 16, (i << 16) + 0xFFFF, (pointer)SoundDummy);

	return 0;
}