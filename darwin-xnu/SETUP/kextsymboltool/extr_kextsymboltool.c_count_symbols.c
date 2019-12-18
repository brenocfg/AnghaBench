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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  issymchar (char) ; 
 char* memchr (char*,char,scalar_t__) ; 

__attribute__((used)) static uint32_t
count_symbols(char * file, vm_size_t file_size)
{
    uint32_t nsyms = 0;
    char *   scan;
    char *   eol;
    char *   next;

    for (scan = file; true; scan = next) {

        eol = memchr(scan, '\n', file_size - (scan - file));
        if (eol == NULL) {
            break;
        }
        next = eol + 1;

       /* Skip empty lines.
        */
        if (eol == scan) {
            continue;
        }

       /* Skip comment lines.
        */
        if (scan[0] == '#') {
            continue;
        }

       /* Scan past any non-symbol characters at the beginning of the line. */
        while ((scan < eol) && !issymchar(*scan)) {
            scan++;
        }

       /* No symbol on line? Move along.
        */
        if (scan == eol) {
            continue;
        }

       /* Skip symbols starting with '.'.
        */
        if (scan[0] == '.') {
            continue;
        }
        nsyms++;
    }
    
    return nsyms;
}