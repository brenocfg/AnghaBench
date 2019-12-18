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
 int H_SUCCESS ; 
 int* hvsi_udbg_buf ; 
 int hvsi_udbg_buf_len ; 
 int plpar_get_term_char (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  vtermno ; 

__attribute__((used)) static int udbg_hvsi_getc_poll(void)
{
	unsigned char ch;
	int rc, i;

	if (hvsi_udbg_buf_len == 0) {
		rc = plpar_get_term_char(vtermno, &hvsi_udbg_buf_len, hvsi_udbg_buf);
		if (rc != H_SUCCESS || hvsi_udbg_buf[0] != 0xff) {
			/* bad read or non-data packet */
			hvsi_udbg_buf_len = 0;
		} else {
			/* remove the packet header */
			for (i = 4; i < hvsi_udbg_buf_len; i++)
				hvsi_udbg_buf[i-4] = hvsi_udbg_buf[i];
			hvsi_udbg_buf_len -= 4;
		}
	}

	if (hvsi_udbg_buf_len <= 0 || hvsi_udbg_buf_len > 256) {
		/* no data ready */
		hvsi_udbg_buf_len = 0;
		return -1;
	}

	ch = hvsi_udbg_buf[0];
	/* shift remaining data down */
	for (i = 1; i < hvsi_udbg_buf_len; i++) {
		hvsi_udbg_buf[i-1] = hvsi_udbg_buf[i];
	}
	hvsi_udbg_buf_len--;

	return ch;
}