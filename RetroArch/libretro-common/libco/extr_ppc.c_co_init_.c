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

/* Variables and functions */
 int PROT_EXEC ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  co_active_handle ; 
 int /*<<< orphan*/  co_create_ (int /*<<< orphan*/ ,uintptr_t) ; 
 int /*<<< orphan*/  co_switch ; 
 scalar_t__ libco_ppc_code ; 
 int /*<<< orphan*/  mprotect (void*,uintptr_t,int) ; 
 int /*<<< orphan*/  state_size ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void co_init_( void )
{
#if LIBCO_MPROTECT
   /* TODO: pre- and post-pad PPC code so that this doesn't make other
      data executable and writable */
   long page_size = sysconf( _SC_PAGESIZE );
   if ( page_size > 0 )
   {
      uintptr_t align = page_size;
      uintptr_t begin = (uintptr_t) libco_ppc_code;
      uintptr_t end   = begin + sizeof libco_ppc_code;

      /* Align beginning and end */
      end   += align - 1;
      end   -= end   % align;
      begin -= begin % align;

      mprotect( (void*) begin, end - begin, PROT_READ | PROT_WRITE | PROT_EXEC );
   }
#endif

   co_active_handle = co_create_( state_size, (uintptr_t) &co_switch );
}