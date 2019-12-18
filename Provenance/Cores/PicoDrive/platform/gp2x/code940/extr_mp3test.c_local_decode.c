#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mp3_offs; int mp3_len; size_t mp3_buffsel; int mp3_lasterr; int /*<<< orphan*/  mp3_errors; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mp3_buffer; int /*<<< orphan*/  mp3dec; } ;

/* Variables and functions */
 int ERR_MP3_INDATA_UNDERFLOW ; 
 int MP3Decode (int /*<<< orphan*/ ,unsigned char**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MP3FindSyncWord (unsigned char*,int) ; 
 unsigned char* mp3_data ; 
 TYPE_2__* shared_ctl ; 
 TYPE_1__* shared_data ; 

void local_decode(void)
{
	int mp3_offs = shared_ctl->mp3_offs;
	unsigned char *readPtr = mp3_data + mp3_offs;
	int bytesLeft = shared_ctl->mp3_len - mp3_offs;
	int offset; // frame offset from readPtr
	int err = 0;

	if (bytesLeft <= 0) return; // EOF, nothing to do

	offset = MP3FindSyncWord(readPtr, bytesLeft);
	if (offset < 0) {
		shared_ctl->mp3_offs = shared_ctl->mp3_len;
		return; // EOF
	}
	readPtr += offset;
	bytesLeft -= offset;

	err = MP3Decode(shared_data->mp3dec, &readPtr, &bytesLeft,
			shared_data->mp3_buffer[shared_ctl->mp3_buffsel], 0);
	if (err) {
		if (err == ERR_MP3_INDATA_UNDERFLOW) {
			shared_ctl->mp3_offs = shared_ctl->mp3_len; // EOF
			return;
		} else if (err <= -6 && err >= -12) {
			// ERR_MP3_INVALID_FRAMEHEADER, ERR_MP3_INVALID_*
			// just try to skip the offending frame..
			readPtr++;
		}
		shared_ctl->mp3_errors++;
		shared_ctl->mp3_lasterr = err;
	}
	shared_ctl->mp3_offs = readPtr - mp3_data;
}