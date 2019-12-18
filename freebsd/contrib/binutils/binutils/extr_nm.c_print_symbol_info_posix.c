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
struct extended_symbol_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_NAME (struct extended_symbol_info*) ; 
 scalar_t__ SYM_SIZE (struct extended_symbol_info*) ; 
 int SYM_TYPE (struct extended_symbol_info*) ; 
 scalar_t__ SYM_VALUE (struct extended_symbol_info*) ; 
 scalar_t__ bfd_is_undefined_symclass (int) ; 
 int /*<<< orphan*/  print_symname (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_value (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_symbol_info_posix (struct extended_symbol_info *info, bfd *abfd)
{
  print_symname ("%s ", SYM_NAME (info), abfd);
  printf ("%c ", SYM_TYPE (info));

  if (bfd_is_undefined_symclass (SYM_TYPE (info)))
    printf ("        ");
  else
    {
      print_value (abfd, SYM_VALUE (info));
      printf (" ");
      if (SYM_SIZE (info))
	print_value (abfd, SYM_SIZE (info));
    }
}