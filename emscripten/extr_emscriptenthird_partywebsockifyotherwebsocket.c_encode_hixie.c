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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int b64_ntop (int /*<<< orphan*/  const*,size_t,char*,size_t) ; 

int encode_hixie(u_char const *src, size_t srclength,
                 char *target, size_t targsize) {
    int sz = 0, len = 0;
    target[sz++] = '\x00';
    len = b64_ntop(src, srclength, target+sz, targsize-sz);
    if (len < 0) {
        return len;
    }
    sz += len;
    target[sz++] = '\xff';
    return sz;
}