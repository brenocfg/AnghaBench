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
 size_t strlen (char*) ; 

__attribute__((used)) static size_t process_line(char* line, char* packet)
{
    size_t count = 0;
    size_t i;

    for (i=0; i< strlen(line); i++) {
        char c = line[i];
        // accept both separators between bytes
        if (c == '-' || c == ' ') {
            ++count;
        // Processing numeric characters
        } else if (c >= '0' && c <= '9') {
            packet[count] *= 16;
            packet[count] += c - '0';
        // Processing alpha-numeric hex characters
        } else if (c >= 'a' && c <= 'f') {
            packet[count] *= 16;
            packet[count] += c - 'a' + 10;
        }
    }

    if (i>0 && strlen(line)>0) {
        count++;
    }
    return count;
}