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

/* Variables and functions */
 scalar_t__ CASSETTE_record ; 
 int /*<<< orphan*/  ESC_enable_sio_patch ; 
 int /*<<< orphan*/  IMG_TAPE_WriteByte (int /*<<< orphan*/ ,int,int) ; 
 int* POKEY_AUDF ; 
 size_t POKEY_CHAN3 ; 
 size_t POKEY_CHAN4 ; 
 int /*<<< orphan*/  cassette_file ; 
 scalar_t__ cassette_writable ; 

void CASSETTE_PutByte(int byte)
{
	if (!ESC_enable_sio_patch && cassette_writable && CASSETTE_record)
		IMG_TAPE_WriteByte(cassette_file, byte, POKEY_AUDF[POKEY_CHAN3] + POKEY_AUDF[POKEY_CHAN4]*0x100);
}