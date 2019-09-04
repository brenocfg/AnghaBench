#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; scalar_t__ datalen; scalar_t__ time; struct TYPE_8__* next; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zbar_symbol_t ;
struct TYPE_9__ {TYPE_1__* cache; } ;
typedef  TYPE_2__ zbar_image_scanner_t ;

/* Variables and functions */
 scalar_t__ CACHE_TIMEOUT ; 
 int /*<<< orphan*/  _zbar_image_scanner_recycle_syms (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline zbar_symbol_t *cache_lookup (zbar_image_scanner_t *iscn,
                                           zbar_symbol_t *sym)
{
    /* search for matching entry in cache */
    zbar_symbol_t **entry = &iscn->cache;
    while(*entry) {
        if((*entry)->type == sym->type &&
           (*entry)->datalen == sym->datalen &&
           !memcmp((*entry)->data, sym->data, sym->datalen))
            break;
        if((sym->time - (*entry)->time) > CACHE_TIMEOUT) {
            /* recycle stale cache entry */
            zbar_symbol_t *next = (*entry)->next;
            (*entry)->next = NULL;
            _zbar_image_scanner_recycle_syms(iscn, *entry);
            *entry = next;
        }
        else
            entry = &(*entry)->next;
    }
    return(*entry);
}