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
struct init_section_info {char* uri; char* byterange; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static void handle_init_section_args(struct init_section_info *info, const char *key,
                                           int key_len, char **dest, int *dest_len)
{
    if (!strncmp(key, "URI=", key_len)) {
        *dest     =        info->uri;
        *dest_len = sizeof(info->uri);
    } else if (!strncmp(key, "BYTERANGE=", key_len)) {
        *dest     =        info->byterange;
        *dest_len = sizeof(info->byterange);
    }
}