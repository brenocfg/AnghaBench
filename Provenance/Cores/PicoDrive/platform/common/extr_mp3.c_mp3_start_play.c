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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int POPT_EN_MCD_CDDA ; 
 int PicoOpt ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ cdda_out_pos ; 
 int decoder_active ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp3_current_file ; 
 int mp3_file_len ; 
 int mp3_file_pos ; 
 int mp3_find_sync_word (unsigned char*,int) ; 
 int /*<<< orphan*/  mp3dec_decode (int /*<<< orphan*/ *,int*,int) ; 
 int mp3dec_start (int /*<<< orphan*/ *,int) ; 

void mp3_start_play(void *f_, int pos1024)
{
	unsigned char buf[2048];
	FILE *f = f_;
	int ret;

	mp3_file_len = mp3_file_pos = 0;
	mp3_current_file = NULL;
	cdda_out_pos = 0;
	decoder_active = 0;

	if (!(PicoOpt & POPT_EN_MCD_CDDA) || f == NULL) // cdda disabled or no file?
		return;

	fseek(f, 0, SEEK_END);
	mp3_file_len = ftell(f);

	// search for first sync word, skipping stuff like ID3 tags
	while (mp3_file_pos < 128*1024) {
		int offs, bytes;

		fseek(f, mp3_file_pos, SEEK_SET);
		bytes = fread(buf, 1, sizeof(buf), f);
		if (bytes < 4)
			break;
		offs = mp3_find_sync_word(buf, bytes);
		if (offs >= 0) {
			mp3_file_pos += offs;
			break;
		}
		mp3_file_pos += bytes - 3;
	}

	// seek..
	if (pos1024 != 0) {
		unsigned long long pos64 = mp3_file_len - mp3_file_pos;
		pos64 *= pos1024;
		mp3_file_pos += pos64 >> 10;
	}

	ret = mp3dec_start(f, mp3_file_pos);
	if (ret != 0) {
		return;
	}

	mp3_current_file = f;
	decoder_active = 1;

	mp3dec_decode(mp3_current_file, &mp3_file_pos, mp3_file_len);
}