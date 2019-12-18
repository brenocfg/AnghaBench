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
typedef  int /*<<< orphan*/  uint32_t ;
struct sh2lib_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_TO_SEND ; 
 int /*<<< orphan*/  NGHTTP2_DATA_FLAG_EOF ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int send_put_data(struct sh2lib_handle *handle, char *buf, size_t length, uint32_t *data_flags)
{
#define DATA_TO_SEND "Hello World"
    int copylen = strlen(DATA_TO_SEND);
    if (copylen < length) {
        printf("[data-prvd] Sending %d bytes\n", copylen);
        memcpy(buf, DATA_TO_SEND, copylen);
    } else {
        copylen = 0;
    }

    (*data_flags) |= NGHTTP2_DATA_FLAG_EOF;
    return copylen;
}