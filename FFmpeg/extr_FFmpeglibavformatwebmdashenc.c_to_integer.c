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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 

__attribute__((used)) static int to_integer(char *p, int len)
{
    int ret;
    char *q = av_malloc(sizeof(char) * len);
    if (!q)
        return AVERROR(ENOMEM);
    av_strlcpy(q, p, len);
    ret = atoi(q);
    av_free(q);
    return ret;
}