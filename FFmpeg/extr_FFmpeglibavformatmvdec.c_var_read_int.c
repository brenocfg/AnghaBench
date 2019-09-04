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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 char* var_read_string (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int var_read_int(AVIOContext *pb, int size)
{
    int v;
    char *s = var_read_string(pb, size);
    if (!s)
        return 0;
    v = strtol(s, NULL, 10);
    av_free(s);
    return v;
}