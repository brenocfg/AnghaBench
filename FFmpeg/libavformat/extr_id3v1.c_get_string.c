#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_3__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_string(AVFormatContext *s, const char *key,
                       const uint8_t *buf, int buf_size)
{
    int i, c;
    char *q, str[512], *first_free_space = NULL;

    q = str;
    for(i = 0; i < buf_size; i++) {
        c = buf[i];
        if (c == '\0')
            break;
        if ((q - str) >= sizeof(str) - 1)
            break;
        if (c == ' ') {
            if (!first_free_space)
                first_free_space = q;
        } else {
            first_free_space = NULL;
        }
        *q++ = c;
    }
    *q = '\0';

    if (first_free_space)
        *first_free_space = '\0';

    if (*str)
        av_dict_set(&s->metadata, key, str, 0);
}