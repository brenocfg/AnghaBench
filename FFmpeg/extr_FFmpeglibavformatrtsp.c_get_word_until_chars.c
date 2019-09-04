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
 int /*<<< orphan*/  SPACE_CHARS ; 
 int /*<<< orphan*/  strchr (char const*,char const) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_word_until_chars(char *buf, int buf_size,
                                 const char *sep, const char **pp)
{
    const char *p;
    char *q;

    p = *pp;
    p += strspn(p, SPACE_CHARS);
    q = buf;
    while (!strchr(sep, *p) && *p != '\0') {
        if ((q - buf) < buf_size - 1)
            *q++ = *p;
        p++;
    }
    if (buf_size > 0)
        *q = '\0';
    *pp = p;
}