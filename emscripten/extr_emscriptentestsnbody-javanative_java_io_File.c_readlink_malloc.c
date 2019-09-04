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
 scalar_t__ XMLVM_ATOMIC_MALLOC (int) ; 
 int /*<<< orphan*/  XMLVM_FREE (char*) ; 
 int readlink (char const*,char*,int) ; 

char * readlink_malloc (const char *filename)
{
    int size = 100;
    char *buffer = NULL;
          
    while (1)
    {
        buffer = (char *) XMLVM_ATOMIC_MALLOC (size);
        int nchars = readlink (filename, buffer, size);
        if (nchars < 0)
        {
            XMLVM_FREE(buffer);
            return NULL;
        }
        if (nchars < size)
            return buffer;
        XMLVM_FREE(buffer);
        size *= 2;
    }
}