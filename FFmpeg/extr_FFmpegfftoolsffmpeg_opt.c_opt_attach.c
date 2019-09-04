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
struct TYPE_2__ {char const** attachments; int nb_attachments; } ;
typedef  TYPE_1__ OptionsContext ;

/* Variables and functions */
 int /*<<< orphan*/  GROW_ARRAY (char const**,int) ; 

__attribute__((used)) static int opt_attach(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    GROW_ARRAY(o->attachments, o->nb_attachments);
    o->attachments[o->nb_attachments - 1] = arg;
    return 0;
}