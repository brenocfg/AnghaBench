#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  keys ;
struct TYPE_5__ {char const* name; } ;
typedef  TYPE_1__ TiffGeoTagKeyName ;

/* Variables and functions */
 TYPE_1__* bsearch (int*,TYPE_1__ const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_id_key ; 

__attribute__((used)) static const char *search_keyval(const TiffGeoTagKeyName *keys, int n, int id)
{
    TiffGeoTagKeyName *r = bsearch(&id, keys, n, sizeof(keys[0]), cmp_id_key);
    if(r)
        return r->name;

    return NULL;
}