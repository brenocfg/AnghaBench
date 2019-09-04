#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_8__ {int quality; int datalen; int data_alloc; int /*<<< orphan*/ * data; int /*<<< orphan*/  syms; int /*<<< orphan*/  time; scalar_t__ cache_count; int /*<<< orphan*/  orient; scalar_t__ npts; int /*<<< orphan*/  type; struct TYPE_8__* next; } ;
typedef  TYPE_2__ zbar_symbol_t ;
struct TYPE_9__ {int /*<<< orphan*/  time; TYPE_1__* recycle; } ;
typedef  TYPE_3__ zbar_image_scanner_t ;
struct TYPE_7__ {int nsyms; TYPE_2__* head; } ;

/* Variables and functions */
 int RECYCLE_BUCKETS ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_ORIENT_UNKNOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  sym_new ; 
 int /*<<< orphan*/ * sym_recycle ; 

inline zbar_symbol_t*
_zbar_image_scanner_alloc_sym (zbar_image_scanner_t *iscn,
                               zbar_symbol_type_t type,
                               int datalen)
{
    /* recycle old or alloc new symbol */
    zbar_symbol_t *sym = NULL;
    int i;
    for(i = 0; i < RECYCLE_BUCKETS - 1; i++)
        if(datalen <= 1 << (i * 2))
            break;

    for(; i > 0; i--)
        if((sym = iscn->recycle[i].head)) {
            STAT(sym_recycle[i]);
            break;
        }

    if(sym) {
        iscn->recycle[i].head = sym->next;
        sym->next = NULL;
        assert(iscn->recycle[i].nsyms);
        iscn->recycle[i].nsyms--;
    }
    else {
        sym = calloc(1, sizeof(zbar_symbol_t));
        STAT(sym_new);
    }

    /* init new symbol */
    sym->type = type;
    sym->quality = 1;
    sym->npts = 0;
    sym->orient = ZBAR_ORIENT_UNKNOWN;
    sym->cache_count = 0;
    sym->time = iscn->time;
    assert(!sym->syms);

    if(datalen > 0) {
        sym->datalen = datalen - 1;
        if(sym->data_alloc < datalen) {
            if(sym->data)
                free(sym->data);
            sym->data_alloc = datalen;
            sym->data = malloc(datalen);
        }
    }
    else {
        if(sym->data)
            free(sym->data);
        sym->data = NULL;
        sym->datalen = sym->data_alloc = 0;
    }
    return(sym);
}