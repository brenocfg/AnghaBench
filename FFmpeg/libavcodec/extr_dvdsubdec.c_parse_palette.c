#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int has_palette; int /*<<< orphan*/ * palette; } ;
typedef  TYPE_1__ DVDSubContext ;

/* Variables and functions */
 scalar_t__ av_isspace (char) ; 
 int /*<<< orphan*/  strtoul (char*,char**,int) ; 

__attribute__((used)) static void parse_palette(DVDSubContext *ctx, char *p)
{
    int i;

    ctx->has_palette = 1;
    for(i=0;i<16;i++) {
        ctx->palette[i] = strtoul(p, &p, 16);
        while(*p == ',' || av_isspace(*p))
            p++;
    }
}