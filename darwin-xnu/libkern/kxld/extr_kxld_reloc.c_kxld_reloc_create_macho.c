#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct scattered_relocation_info {int r_address; scalar_t__ r_type; scalar_t__ r_value; int /*<<< orphan*/  r_length; int /*<<< orphan*/  r_pcrel; } ;
struct relocation_info {int r_address; scalar_t__ r_extern; scalar_t__ r_symbolnum; scalar_t__ r_type; int /*<<< orphan*/  r_length; int /*<<< orphan*/  r_pcrel; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_7__ {int address; scalar_t__ reloc_type; scalar_t__ target; int pair_address; scalar_t__ pair_target; void* pair_target_type; void* target_type; int /*<<< orphan*/  length; int /*<<< orphan*/  pcrel; } ;
struct TYPE_6__ {scalar_t__ (* reloc_get_pair_type ) (scalar_t__) ;scalar_t__ (* reloc_has_got ) (scalar_t__) ;scalar_t__ may_scatter; scalar_t__ (* reloc_has_pair ) (scalar_t__) ;} ;
typedef  TYPE_1__ KXLDRelocator ;
typedef  TYPE_2__ KXLDReloc ;
typedef  struct relocation_info const KXLDArray ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 void* KXLD_TARGET_GOT ; 
 void* KXLD_TARGET_LOOKUP ; 
 void* KXLD_TARGET_NONE ; 
 void* KXLD_TARGET_SECTNUM ; 
 void* KXLD_TARGET_SYMBOLNUM ; 
 void* KXLD_TARGET_VALUE ; 
 scalar_t__ R_ABS ; 
 int R_SCATTERED ; 
 int /*<<< orphan*/  check (struct relocation_info const*) ; 
 scalar_t__ count_relocatable_relocs (TYPE_1__ const*,struct relocation_info const*,scalar_t__) ; 
 int /*<<< orphan*/  finish ; 
 TYPE_2__* kxld_array_get_item (struct relocation_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_array_init (struct relocation_info const*,int,scalar_t__) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__) ; 
 scalar_t__ stub3 (scalar_t__) ; 
 scalar_t__ stub4 (scalar_t__) ; 

kern_return_t
kxld_reloc_create_macho(KXLDArray *relocarray, const KXLDRelocator *relocator, 
    const struct relocation_info *srcs, u_int nsrcs)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDReloc *reloc = NULL;
    u_int nrelocs = 0;
    const struct relocation_info *src = NULL;
    const struct scattered_relocation_info *scatsrc = NULL;
    u_int i = 0;
    u_int reloc_index = 0;

    check(relocarray);
    check(srcs);

    /* If there are no relocation entries, just return */
    if (!nsrcs) {
        rval = KERN_SUCCESS;
        goto finish;
    }

    /* Count the number of non-pair relocs */
    nrelocs = count_relocatable_relocs(relocator, srcs, nsrcs);

    if (nrelocs) {

        /* Allocate the array of relocation entries */

        rval = kxld_array_init(relocarray, sizeof(KXLDReloc), nrelocs);
        require_noerr(rval, finish);

        /* Initialize the relocation entries */
        
        for (i = 0; i < nsrcs; ++i) {
            src = srcs + i;
            scatsrc = (const struct scattered_relocation_info *) src;

            /* A section-based relocation entry can be skipped for absolute 
             * symbols.
             */

            if (!(relocator->may_scatter && (src->r_address & R_SCATTERED)) &&
                !(src->r_extern) && (R_ABS == src->r_symbolnum))
            {
                continue;
            }
            
            /* Pull out the data from the relocation entries.  The target_type
             * depends on the r_extern bit:
             *  Scattered -> Section Lookup by Address
             *  Local (not extern) -> Section by Index
             *  Extern -> Symbolnum by Index
             */
            reloc = kxld_array_get_item(relocarray, reloc_index++);
            if (relocator->may_scatter && (src->r_address & R_SCATTERED)) {
                reloc->address = scatsrc->r_address;
                reloc->pcrel = scatsrc->r_pcrel;
                reloc->length = scatsrc->r_length;
                reloc->reloc_type = scatsrc->r_type;
                reloc->target = scatsrc->r_value;
                reloc->target_type = KXLD_TARGET_LOOKUP;
            } else {
                reloc->address = src->r_address;
                reloc->pcrel = src->r_pcrel;
                reloc->length = src->r_length;
                reloc->reloc_type = src->r_type;
                reloc->target = src->r_symbolnum;

                if (0 == src->r_extern) {
                    reloc->target_type = KXLD_TARGET_SECTNUM;
                    reloc->target -= 1;
                } else {
                    reloc->target_type = KXLD_TARGET_SYMBOLNUM;
                }
            }
            
            /* Find the pair entry if it exists */

            if (relocator->reloc_has_pair(reloc->reloc_type)) {
                ++i;
                require_action(i < nsrcs, finish, rval=KERN_FAILURE);

                src = srcs + i;
                scatsrc = (const struct scattered_relocation_info *) src;
                 
                if (relocator->may_scatter && (src->r_address & R_SCATTERED)) {
                    require_action(relocator->reloc_get_pair_type(
                        reloc->reloc_type) == scatsrc->r_type,
                        finish, rval=KERN_FAILURE);
                    reloc->pair_address= scatsrc->r_address;
                    reloc->pair_target = scatsrc->r_value;
                    reloc->pair_target_type = KXLD_TARGET_LOOKUP;
                } else {
                    require_action(relocator->reloc_get_pair_type(
                        reloc->reloc_type) == scatsrc->r_type,
                        finish, rval=KERN_FAILURE);
                    reloc->pair_address = scatsrc->r_address;
                    if (src->r_extern) {
                        reloc->pair_target = src->r_symbolnum;
                        reloc->pair_target_type = KXLD_TARGET_SYMBOLNUM;
                    } else {
                        reloc->pair_target = src->r_address;
                        reloc->pair_target_type = KXLD_TARGET_VALUE;
                    }
                }
            } else {
                reloc->pair_target = 0;
                if (relocator->reloc_has_got(reloc->reloc_type)) {
                   reloc->pair_target_type = KXLD_TARGET_GOT;
                } else {
                   reloc->pair_target_type = KXLD_TARGET_NONE;
                }
            }
       } // for...
    }
    rval = KERN_SUCCESS;

finish:
    return rval;
}