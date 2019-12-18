#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mincount; } ;
struct arg_rex {scalar_t__ count; TYPE_1__ hdr; } ;

/* Variables and functions */
 int EMINCOUNT ; 

__attribute__((used)) static int arg_rex_checkfn(struct arg_rex *parent)
{
    int errorcode = (parent->count < parent->hdr.mincount) ? EMINCOUNT : 0;
    //struct privhdr *priv = (struct privhdr*)parent->hdr.priv;

    /* free the regex "program" we constructed in resetfn */
    //regfree(&(priv->regex));

    /*printf("%s:checkfn(%p) returns %d\n",__FILE__,parent,errorcode);*/
    return errorcode;
}