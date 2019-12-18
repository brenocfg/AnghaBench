#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ apetag; } ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ADTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_ape_write_tag (TYPE_1__*) ; 

__attribute__((used)) static int adts_write_trailer(AVFormatContext *s)
{
    ADTSContext *adts = s->priv_data;

    if (adts->apetag)
        ff_ape_write_tag(s);

    return 0;
}