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
typedef  int /*<<< orphan*/  uint8_t ;
struct sh2lib_handle {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  nghttp2_session ;

/* Variables and functions */
 int callback_send_inner (struct sh2lib_handle*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static ssize_t callback_send(nghttp2_session *session, const uint8_t *data,
                             size_t length, int flags, void *user_data)
{
    int rv = 0;
    struct sh2lib_handle *hd = user_data;

    int copy_offset = 0;
    int pending_data = length;

    /* Send data in 1000 byte chunks */
    while (copy_offset != length) {
        int chunk_len = pending_data > 1000 ? 1000 : pending_data;
        int subrv = callback_send_inner(hd, data + copy_offset, chunk_len);
        if (subrv <= 0) {
            if (copy_offset == 0) {
                /* If no data is transferred, send the error code */
                rv = subrv;
            }
            break;
        }
        copy_offset += subrv;
        pending_data -= subrv;
        rv += subrv;
    }
    return rv;
}