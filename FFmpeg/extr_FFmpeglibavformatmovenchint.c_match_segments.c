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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int match_segments(const uint8_t *haystack, int h_len,
                          const uint8_t *needle, int n_pos, int n_len,
                          int *match_h_offset_ptr, int *match_n_offset_ptr,
                          int *match_len_ptr)
{
    int h_pos;
    for (h_pos = 0; h_pos < h_len; h_pos++) {
        int match_len = 0;
        int match_h_pos, match_n_pos;

        /* Check how many bytes match at needle[n_pos] and haystack[h_pos] */
        while (h_pos + match_len < h_len && n_pos + match_len < n_len &&
               needle[n_pos + match_len] == haystack[h_pos + match_len])
            match_len++;
        if (match_len <= 8)
            continue;

        /* If a sufficiently large match was found, try to expand
         * the matched segment backwards. */
        match_h_pos = h_pos;
        match_n_pos = n_pos;
        while (match_n_pos > 0 && match_h_pos > 0 &&
               needle[match_n_pos - 1] == haystack[match_h_pos - 1]) {
            match_n_pos--;
            match_h_pos--;
            match_len++;
        }
        if (match_len <= 14)
            continue;
        *match_h_offset_ptr = match_h_pos;
        *match_n_offset_ptr = match_n_pos;
        *match_len_ptr = match_len;
        return 0;
    }
    return -1;
}