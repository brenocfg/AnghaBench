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
struct internal_exec {int /*<<< orphan*/  a_info; } ;
struct external_exec {int /*<<< orphan*/  e_info; } ;
typedef  int /*<<< orphan*/  bfd_target ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ EXEC_BYTES_SIZE ; 
 int /*<<< orphan*/  H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ N_BADMAG (struct internal_exec) ; 
 int /*<<< orphan*/  const* aout_32_some_aout_object_p (int /*<<< orphan*/ *,struct internal_exec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_out_callback ; 
 scalar_t__ bfd_bread (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bout_swap_exec_header_in (int /*<<< orphan*/ *,struct external_exec*,struct internal_exec*) ; 

__attribute__((used)) static const bfd_target *
b_out_object_p (bfd *abfd)
{
  struct internal_exec anexec;
  struct external_exec exec_bytes;
  bfd_size_type amt = EXEC_BYTES_SIZE;

  if (bfd_bread ((void *) &exec_bytes, amt, abfd) != amt)
    {
      if (bfd_get_error () != bfd_error_system_call)
	bfd_set_error (bfd_error_wrong_format);
      return 0;
    }

  anexec.a_info = H_GET_32 (abfd, exec_bytes.e_info);

  if (N_BADMAG (anexec))
    {
      bfd_set_error (bfd_error_wrong_format);
      return 0;
    }

  bout_swap_exec_header_in (abfd, &exec_bytes, &anexec);
  return aout_32_some_aout_object_p (abfd, &anexec, b_out_callback);
}