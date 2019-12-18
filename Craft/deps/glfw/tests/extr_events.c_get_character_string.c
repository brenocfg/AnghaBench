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
 int wctomb (char*,int) ; 

__attribute__((used)) static const char* get_character_string(int codepoint)
{
    // This assumes UTF-8, which is stupid
    static char result[6 + 1];

    int length = wctomb(result, codepoint);
    if (length == -1)
        length = 0;

    result[length] = '\0';
    return result;
}