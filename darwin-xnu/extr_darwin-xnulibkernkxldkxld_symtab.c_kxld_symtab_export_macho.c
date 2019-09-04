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
typedef  void* uint32_t ;
typedef  int u_long ;
typedef  int u_char ;
struct symtab_command {int symoff; int strsize; int nsyms; int stroff; void* cmdsize; int /*<<< orphan*/  cmd; } ;
struct nlist_64 {int dummy; } ;
struct nlist {int dummy; } ;
typedef  int kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  KXLDSymtabIterator ;
typedef  int KXLDSymtab ;
typedef  TYPE_1__ KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KERN_FAILURE ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  KXLD_3264_FUNC (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int*,char*,int*,int) ; 
 int /*<<< orphan*/  LC_SYMTAB ; 
 int /*<<< orphan*/  check (int const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_sym_export_macho_32 ; 
 int /*<<< orphan*/  kxld_sym_export_macho_64 ; 
 int /*<<< orphan*/  kxld_sym_is_defined_locally ; 
 TYPE_1__* kxld_symtab_iterator_get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_init (int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kxld_symtab_iterator_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  require_noerr (int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

kern_return_t
kxld_symtab_export_macho(const KXLDSymtab *symtab, u_char *buf, 
    u_long *header_offset, u_long header_size,
    u_long *data_offset, u_long data_size,
    boolean_t is_32_bit)
{
    kern_return_t rval = KERN_FAILURE;
    KXLDSymtabIterator iter;
    KXLDSym *sym = NULL;
    struct symtab_command *symtabhdr = NULL;
    u_char *nl = NULL;
    u_long nlistsize = 0;
    char *strtab = NULL;
    u_long stroff = 1; /* strtab start padding */

    check(symtab);
    check(buf);
    check(header_offset);
    check(data_offset);

    require_action(sizeof(*symtabhdr) <= header_size - *header_offset,
        finish, rval=KERN_FAILURE);
    symtabhdr = (struct symtab_command *) ((void *) (buf + *header_offset));
    *header_offset += sizeof(*symtabhdr);
    
    /* Initialize the symbol table header */

    // note - this assumes LC_SYMTAB is always before the LC_DYSYMTAB in the
    // macho header we are processing.
    symtabhdr->cmd = LC_SYMTAB;
    symtabhdr->cmdsize = (uint32_t) sizeof(*symtabhdr);
    symtabhdr->symoff = (uint32_t) *data_offset;
    symtabhdr->strsize = 1; /* strtab start padding */

    /* Find the size of the symbol and string tables */

    kxld_symtab_iterator_init(&iter, symtab, 
        kxld_sym_is_defined_locally, FALSE);

    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        symtabhdr->nsyms++;
        symtabhdr->strsize += (uint32_t) (strlen(sym->name) + 1);
    }

    if (is_32_bit) {
        nlistsize = sizeof(struct nlist);
    } else {
        nlistsize = sizeof(struct nlist_64);
    }

    symtabhdr->stroff = (uint32_t) (symtabhdr->symoff + 
        (symtabhdr->nsyms * nlistsize));
    require_action(symtabhdr->stroff + symtabhdr->strsize <= data_size, finish,
        rval=KERN_FAILURE);

    /* Get pointers to the symbol and string tables */
    nl = buf + symtabhdr->symoff;
    strtab = (char *) (buf + symtabhdr->stroff);

    /* Copy over the symbols */

    kxld_symtab_iterator_reset(&iter);
    while ((sym = kxld_symtab_iterator_get_next(&iter))) {
        KXLD_3264_FUNC(is_32_bit, rval,
            kxld_sym_export_macho_32, kxld_sym_export_macho_64,
            sym, nl, strtab, &stroff, symtabhdr->strsize);
        require_noerr(rval, finish);

        nl += nlistsize;
        stroff += rval;
    }

    /* Update the data offset */
    *data_offset += (symtabhdr->nsyms * nlistsize) + stroff;

    *data_offset = (*data_offset + 7) & ~7;
    // at this point data_offset will be the offset just past the
    // symbols and strings in the __LINKEDIT data
    

#if SPLIT_KEXTS_DEBUG
    {
        kxld_log(kKxldLogLinking, kKxldLogErr,
                 " %p to %p (size %lu) symtabhdr <%s>",
                 (void *) symtabhdr,
                 (void *) ((u_char *)symtabhdr + sizeof(*symtabhdr)),
                 sizeof(*symtabhdr),
                 __func__);
      
        kxld_log(kKxldLogLinking, kKxldLogErr,
                 " symtabhdr %p cmdsize %u symoff %u nsyms %u stroff %u strsize %u <%s>",
                 (void *) symtabhdr,
                 symtabhdr->cmdsize,
                 symtabhdr->symoff,
                 symtabhdr->nsyms,
                 symtabhdr->stroff,
                 symtabhdr->strsize,
                 __func__);
    }
#endif

    rval = KERN_SUCCESS;
    
finish:
   return rval;
}