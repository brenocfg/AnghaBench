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
 int ERR_MP3_MAINDATA_UNDERFLOW ; 
 int MP3Decode (int /*<<< orphan*/ ,unsigned char**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* mp3_data ; 
 int mp3_find_sync_word (unsigned char*,int) ; 
 int /*<<< orphan*/  set_if_not_changed (int*,int,int) ; 
 TYPE_2__* shared_ctl ; 
 TYPE_1__* shared_data ; 

__attribute__((used)) static void mp3_decode(void)
{
	int mp3_offs = shared_ctl->mp3_offs;
	unsigned char *readPtr = mp3_data + mp3_offs;
	int bytesLeft = shared_ctl->mp3_len - mp3_offs;
	int offset; // frame offset from readPtr
	int retries = 0, err;

	if (bytesLeft <= 0) return; // EOF, nothing to do

	for (retries = 0; retries < 2; retries++)
	{
		offset = mp3_find_sync_word(readPtr, bytesLeft);
		if (offset < 0)
			goto set_eof;

		readPtr += offset;
		bytesLeft -= offset;

		err = MP3Decode(shared_data->mp3dec, &readPtr, &bytesLeft,
				shared_data->mp3_buffer[shared_ctl->mp3_buffsel], 0);
		if (err) {
			if (err == ERR_MP3_MAINDATA_UNDERFLOW)
				// just need another frame
				continue;

			if (err == ERR_MP3_INDATA_UNDERFLOW)
				goto set_eof;

			if (err <= -6 && err >= -12) {
				// ERR_MP3_INVALID_FRAMEHEADER, ERR_MP3_INVALID_*
				// just try to skip the offending frame..
				readPtr++;
				bytesLeft--;
				continue;
			}
			shared_ctl->mp3_errors++;
			shared_ctl->mp3_lasterr = err;
		}
		break;
	}

	set_if_not_changed(&shared_ctl->mp3_offs, mp3_offs, readPtr - mp3_data);
	return;

set_eof:
	set_if_not_changed(&shared_ctl->mp3_offs, mp3_offs, shared_ctl->mp3_len);
}