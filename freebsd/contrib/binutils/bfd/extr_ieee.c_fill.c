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
typedef  void* bfd_size_type ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_bread (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_bfd ; 
 void* input_ptr ; 
 void* input_ptr_end ; 
 void* input_ptr_start ; 

__attribute__((used)) static void
fill (void)
{
  bfd_size_type amt = input_ptr_end - input_ptr_start;
  /* FIXME: Check return value.  I'm not sure whether it needs to read
     the entire buffer or not.  */
  bfd_bread ((void *) input_ptr_start, amt, input_bfd);
  input_ptr = input_ptr_start;
}