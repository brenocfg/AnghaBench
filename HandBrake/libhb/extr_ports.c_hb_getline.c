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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 char* realloc (char*,size_t) ; 

size_t hb_getline(char ** lineptr, size_t * n, FILE * fp)
{
#ifdef SYS_MINGW
    char   * bufptr = NULL;
    char   * p      = bufptr;
    size_t   size;
    int      c;

    if (lineptr == NULL)
    {
        return -1;
    }
    if (fp == NULL)
    {
        return -1;
    }
    if (n == NULL)
    {
        return -1;
    }
    bufptr = *lineptr;
    size   = *n;

    c = fgetc(fp);
    if (c == EOF)
    {
        return -1;
    }
    if (bufptr == NULL)
    {
        bufptr = malloc(128);
        if (bufptr == NULL)
        {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF)
    {
        if ((p - bufptr) >= (size - 1))
        {
            char * tmp;
            size = size + 128;
            tmp = realloc(bufptr, size);
            if (tmp == NULL)
            {
                free(bufptr);
                return -1;
            }
            p = tmp + (p - bufptr);
            bufptr = tmp;
        }
        *p++ = c;
        if (c == '\n')
        {
            break;
        }
        c = fgetc(fp);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
#else
    return getline(lineptr, n, fp);
#endif
}