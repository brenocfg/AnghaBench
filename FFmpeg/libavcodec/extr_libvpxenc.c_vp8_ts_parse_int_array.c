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
 char* av_strtok (char*,char*,char**) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vp8_ts_parse_int_array(int *dest, char *value, size_t value_len, int max_entries)
{
    int dest_idx = 0;
    char *saveptr = NULL;
    char *token = av_strtok(value, ",", &saveptr);

    while (token && dest_idx < max_entries) {
        dest[dest_idx++] = strtoul(token, NULL, 10);
        token = av_strtok(NULL, ",", &saveptr);
    }
}