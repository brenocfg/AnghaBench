#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; scalar_t__ time; scalar_t__ cache_count; struct TYPE_10__* next; int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; int /*<<< orphan*/  modifiers; int /*<<< orphan*/  configs; } ;
typedef  TYPE_1__ zbar_symbol_t ;
struct TYPE_11__ {scalar_t__** sym_configs; TYPE_1__* cache; scalar_t__ enable_cache; } ;
typedef  TYPE_2__ zbar_image_scanner_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ CACHE_HYSTERESIS ; 
 scalar_t__ CACHE_PROXIMITY ; 
 int _zbar_get_symbol_hash (int) ; 
 TYPE_1__* _zbar_image_scanner_alloc_sym (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* cache_lookup (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cache_sym (zbar_image_scanner_t *iscn,
                              zbar_symbol_t *sym)
{
    if(iscn->enable_cache) {
        uint32_t age, near_thresh, far_thresh, dup;
        zbar_symbol_t *entry = cache_lookup(iscn, sym);
        if(!entry) {
            /* FIXME reuse sym */
            entry = _zbar_image_scanner_alloc_sym(iscn, sym->type,
                                                  sym->datalen + 1);
            entry->configs = sym->configs;
            entry->modifiers = sym->modifiers;
            memcpy(entry->data, sym->data, sym->datalen);
            entry->time = sym->time - CACHE_HYSTERESIS;
            entry->cache_count = 0;
            /* add to cache */
            entry->next = iscn->cache;
            iscn->cache = entry;
        }

        /* consistency check and hysteresis */
        age = sym->time - entry->time;
        entry->time = sym->time;
        near_thresh = (age < CACHE_PROXIMITY);
        far_thresh = (age >= CACHE_HYSTERESIS);
        dup = (entry->cache_count >= 0);
        if((!dup && !near_thresh) || far_thresh) {
            int type = sym->type;
            int h = _zbar_get_symbol_hash(type);
            entry->cache_count = -iscn->sym_configs[0][h];
        }
        else if(dup || near_thresh)
            entry->cache_count++;

        sym->cache_count = entry->cache_count;
    }
    else
        sym->cache_count = 0;
}