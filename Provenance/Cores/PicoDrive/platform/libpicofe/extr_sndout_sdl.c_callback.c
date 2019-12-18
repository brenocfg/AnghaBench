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
typedef  int /*<<< orphan*/  Uint8 ;

/* Variables and functions */
 int BUF_LEN ; 
 int BUF_MASK ; 
 scalar_t__ buf ; 
 int buf_r ; 
 int buf_w ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void callback(void *userdata, Uint8 *stream, int len)
{
	int have = (buf_w - buf_r) & BUF_MASK;
	int buf_left = BUF_LEN - buf_r;

	len /= 2;
	if (have > len)
		have = len;
	if (have > 0) {
		if (have > buf_left) {
			memcpy(stream, buf + buf_r, buf_left * 2);
			stream += buf_left * 2;
			buf_r = 0;
			have -= buf_left;
			len -= buf_left;
		}
		memcpy(stream, buf + buf_r, have * 2);
		stream += have * 2;
		buf_r = (buf_r + have) & BUF_MASK;
		len -= have;
	}

	if (len > 0) {
		// put in some silence..
		memset(stream, 0, len * 2);
	}
}