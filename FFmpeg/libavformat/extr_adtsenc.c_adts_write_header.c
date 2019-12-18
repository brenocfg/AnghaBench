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
struct TYPE_6__ {scalar_t__ id3v2tag; } ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ADTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int /*<<< orphan*/  ff_id3v2_write_simple (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adts_write_header(AVFormatContext *s)
{
    ADTSContext *adts = s->priv_data;

    if (adts->id3v2tag)
        ff_id3v2_write_simple(s, 4, ID3v2_DEFAULT_MAGIC);

    return 0;
}