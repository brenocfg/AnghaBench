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
 int /*<<< orphan*/  isprint (char) ; 
 size_t snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t chrtos(char *buf, size_t size, char byte) {
    size_t len = 0;

    switch(byte) {
    case '\\':
    case '"':
        len = snprintf(buf,size,"\"\\%c\"",byte);
        break;
    case '\n': len = snprintf(buf,size,"\"\\n\""); break;
    case '\r': len = snprintf(buf,size,"\"\\r\""); break;
    case '\t': len = snprintf(buf,size,"\"\\t\""); break;
    case '\a': len = snprintf(buf,size,"\"\\a\""); break;
    case '\b': len = snprintf(buf,size,"\"\\b\""); break;
    default:
        if (isprint(byte))
            len = snprintf(buf,size,"\"%c\"",byte);
        else
            len = snprintf(buf,size,"\"\\x%02x\"",(unsigned char)byte);
        break;
    }

    return len;
}