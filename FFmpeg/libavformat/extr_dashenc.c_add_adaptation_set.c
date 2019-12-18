#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_10__ {TYPE_1__* priv_data; } ;
struct TYPE_9__ {int media_type; } ;
struct TYPE_8__ {int nb_as; TYPE_2__* as; } ;
typedef  TYPE_1__ DASHContext ;
typedef  TYPE_2__ AdaptationSet ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_realloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int add_adaptation_set(AVFormatContext *s, AdaptationSet **as, enum AVMediaType type)
{
    DASHContext *c = s->priv_data;

    void *mem = av_realloc(c->as, sizeof(*c->as) * (c->nb_as + 1));
    if (!mem)
        return AVERROR(ENOMEM);
    c->as = mem;
    ++c->nb_as;

    *as = &c->as[c->nb_as - 1];
    memset(*as, 0, sizeof(**as));
    (*as)->media_type = type;

    return 0;
}