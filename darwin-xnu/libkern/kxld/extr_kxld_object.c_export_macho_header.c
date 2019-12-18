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
typedef  int /*<<< orphan*/  const u_long ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  const u_char ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  KXLDObject ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KXLD_3264_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  check (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  export_macho_header_32 ; 
 int /*<<< orphan*/  export_macho_header_64 ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  kxld_object_is_32_bit (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  require_noerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
export_macho_header(const KXLDObject *object, u_char *buf, u_int ncmds,
    u_long *header_offset, u_long header_size)
{
    kern_return_t rval = KERN_FAILURE;

    check(object);
    check(buf);
    check(header_offset);

    KXLD_3264_FUNC(kxld_object_is_32_bit(object), rval, 
        export_macho_header_32, export_macho_header_64, 
        object, buf, ncmds, header_offset, header_size);
    require_noerr(rval, finish);

    rval = KERN_SUCCESS;

finish:
   return rval;
}