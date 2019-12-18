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
 int /*<<< orphan*/  SEEK_SET ; 
 int fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int try_get_bitrate (unsigned char*,int) ; 

int mp3_get_bitrate(void *f_, int len)
{
	unsigned char buf[2048];
	FILE *f = f_;
	int retval = -1;
	int ret;

	memset(buf, 0, sizeof(buf));

	fseek(f, 0, SEEK_SET);
	ret = fread(buf, 1, sizeof(buf), f);
	if (ret != sizeof(buf))
		goto out;

	ret = try_get_bitrate(buf, sizeof(buf));
	if (ret <= 0) {
		// try to read somewhere around the middle
		fseek(f, len / 2, SEEK_SET);
		ret = fread(buf, 1, sizeof(buf), f);
		if (ret == sizeof(buf))
			ret = try_get_bitrate(buf, sizeof(buf));
	}
	if (ret > 0)
		retval = ret;

	//printf("bitrate: %i\n", retval);

out:
	fseek(f, 0, SEEK_SET);
	return retval;
}