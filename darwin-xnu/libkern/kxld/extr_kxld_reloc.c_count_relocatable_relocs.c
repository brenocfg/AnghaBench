#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct scattered_relocation_info {int /*<<< orphan*/  r_type; } ;
struct relocation_info {int r_address; scalar_t__ r_extern; scalar_t__ r_symbolnum; int /*<<< orphan*/  r_type; scalar_t__ (* reloc_has_pair ) (int /*<<< orphan*/ ) ;} ;
typedef  struct relocation_info KXLDRelocator ;

/* Variables and functions */
 scalar_t__ R_ABS ; 
 int R_SCATTERED ; 
 int /*<<< orphan*/  check (struct relocation_info const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
count_relocatable_relocs(const KXLDRelocator *relocator,
    const struct relocation_info *relocs, u_int nrelocs)
{
    u_int num_nonpair_relocs = 0;
    u_int i = 0;
    const struct relocation_info *reloc = NULL;
    const struct scattered_relocation_info *sreloc = NULL;

    check(relocator);
    check(relocs);

    /* Loop over all of the relocation entries */

    num_nonpair_relocs = 1;
    for (i = 1; i < nrelocs; ++i) {
        reloc = relocs + i;

        if (reloc->r_address & R_SCATTERED) {
            /* A scattered relocation entry is relocatable as long as it's not a
             * pair.
             */
            sreloc = (const struct scattered_relocation_info *) reloc;

            num_nonpair_relocs += 
                !relocator->reloc_has_pair(sreloc->r_type);
        } else {
            /* A normal relocation entry is relocatable if it is not a pair and
             * if it is not a section-based relocation for an absolute symbol.
             */
            num_nonpair_relocs += 
                !(relocator->reloc_has_pair(reloc->r_type)
                 || (0 == reloc->r_extern && R_ABS == reloc->r_symbolnum));
        }

    }
    
    return num_nonpair_relocs;
}