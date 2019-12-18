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
typedef  size_t uint8_t ;

/* Variables and functions */
 char** eddystone_url_encoding ; 
 char** eddystone_url_prefix ; 
 scalar_t__ esp_eddystone_is_char_invalid (size_t const) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static char* esp_eddystone_resolve_url_scheme(const uint8_t *url_start, const uint8_t *url_end)
{
    int pos = 0;
    static char url_buf[100] = {0};
    const uint8_t *p = url_start;

    pos += sprintf(&url_buf[pos], "%s", eddystone_url_prefix[*p++]);

    for (; p <= url_end; p++) {
        if (esp_eddystone_is_char_invalid((*p))) {
            pos += sprintf(&url_buf[pos], "%s", eddystone_url_encoding[*p]);
        } else {
            pos += sprintf(&url_buf[pos], "%c", *p);
        }
    }
    return url_buf;
}