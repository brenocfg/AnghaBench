#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct playlist {int dummy; } ;
struct TYPE_4__ {int n_playlists; struct playlist** playlists; } ;
typedef  TYPE_1__ HLSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  new_variant (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ensure_playlist(HLSContext *c, struct playlist **pls, const char *url)
{
    if (*pls)
        return 0;
    if (!new_variant(c, NULL, url, NULL))
        return AVERROR(ENOMEM);
    *pls = c->playlists[c->n_playlists - 1];
    return 0;
}