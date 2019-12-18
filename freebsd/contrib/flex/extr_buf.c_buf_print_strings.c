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
struct Buf {int nelts; scalar_t__ elts; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 

struct Buf *buf_print_strings(struct Buf * buf, FILE* out)
{
    int i;

    if(!buf || !out)
        return buf;

    for (i=0; i < buf->nelts; i++){
        const char * s = ((char**)buf->elts)[i];
        if(s)
            fprintf(out, "%s", s);
    }
    return buf;
}