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
struct TYPE_6__ {int /*<<< orphan*/  trailer_size; scalar_t__ trailer; } ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASSContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  purge_dialogues (TYPE_1__*,int) ; 

__attribute__((used)) static int write_trailer(AVFormatContext *s)
{
    ASSContext *ass = s->priv_data;

    purge_dialogues(s, 1);

    if (ass->trailer) {
        avio_write(s->pb, ass->trailer, ass->trailer_size);
    }

    return 0;
}