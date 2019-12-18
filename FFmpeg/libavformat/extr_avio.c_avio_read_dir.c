#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* prot; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_8__ {TYPE_2__* url_context; } ;
struct TYPE_6__ {int (* url_read_dir ) (TYPE_2__*,int /*<<< orphan*/ **) ;} ;
typedef  int /*<<< orphan*/  AVIODirEntry ;
typedef  TYPE_3__ AVIODirContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  avio_free_directory_entry (int /*<<< orphan*/ **) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ **) ; 

int avio_read_dir(AVIODirContext *s, AVIODirEntry **next)
{
    URLContext *h;
    int ret;

    if (!s || !s->url_context)
        return AVERROR(EINVAL);
    h = s->url_context;
    if ((ret = h->prot->url_read_dir(h, next)) < 0)
        avio_free_directory_entry(next);
    return ret;
}