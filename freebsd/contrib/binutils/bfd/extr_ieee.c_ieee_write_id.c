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
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t bfd_bwrite (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_extension_length_1_enum ; 
 int /*<<< orphan*/  ieee_extension_length_2_enum ; 
 int /*<<< orphan*/  ieee_write_2bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bfd_boolean
ieee_write_id (bfd *abfd, const char *id)
{
  size_t length = strlen (id);

  if (length <= 127)
    {
      if (! ieee_write_byte (abfd, (bfd_byte) length))
	return FALSE;
    }
  else if (length < 255)
    {
      if (! ieee_write_byte (abfd, ieee_extension_length_1_enum)
	  || ! ieee_write_byte (abfd, (bfd_byte) length))
	return FALSE;
    }
  else if (length < 65535)
    {
      if (! ieee_write_byte (abfd, ieee_extension_length_2_enum)
	  || ! ieee_write_2bytes (abfd, (int) length))
	return FALSE;
    }
  else
    {
      (*_bfd_error_handler)
	(_("%s: string too long (%d chars, max 65535)"),
	 bfd_get_filename (abfd), length);
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  if (bfd_bwrite ((void *) id, (bfd_size_type) length, abfd) != length)
    return FALSE;
  return TRUE;
}